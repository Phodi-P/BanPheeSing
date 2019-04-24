#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions
#include "Kairos/Timestep.hpp"

#include "door.h"
#include "player.h"
#include "npc.h"
#include "ghost.h"
#include "text_box.h"
#include "tilemap.h"
#include "solid_obj.h"
#include "trigger_obj.h"
#include "map_parser.h"

enum npcFormation
{
	front_line = 0,
	back_line = 1,
	follow_line = 2
};

//Functions prototype
void resizeView(const sf::RenderWindow &, sf::View &);
void npcsMove(std::vector<Npc*> &, Player &, npcFormation);

//Global Variables
sf::Vector2f mousePosition = { 0,0 }, ghostPos = { 0,0 };
npcFormation npcFormat = follow_line;



int main()
	{
	//Create windows and view
	sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WindowWidth, WindowHeight));
	//sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha");
	window.setVerticalSyncEnabled(true);

	//Create timestep object
	kairos::Timestep timestep;

	//Create NPCs and Player Objects
	Player Player(".\\textures\\a_sprite.png",32,32,4,3);
	Player.setScale(4.0f, 4.0f);
	Player.setPos({ 710,865 });

	Npc Red({ 100,100 }, ".\\textures\\red_sprite.png", 32, 32, 4, 3, "แดง");
	Red.setScale(4.0f, 4.0f);
	Red.setPos(Player.getPos());

	Npc Green({ 200,100 }, ".\\textures\\green_sprite.png", 32, 32, 4, 3, "เขียว");
	Green.setScale(4.0f, 4.0f);
	Green.setPos(Player.getPos());

	Npc Koy({ 300,100 }, ".\\textures\\koy_sprite.png", 32, 32, 4, 3, "ก้อย");
	Koy.setScale(4.0f, 4.0f);
	Koy.setPos(Player.getPos());

	std::vector<Npc*> NPCs;
	NPCs.push_back(&Red);
	NPCs.push_back(&Green);
	NPCs.push_back(&Koy);

	Ghost Ghost(sf::Vector2f(0.0f,0.0f), ".\\textures\\ghost_sprite.png",96 ,192 ,4 ,3);
	Ghost.setScale(1.5f, 1.5f);
	Ghost.setSpd(3.0f);
	sf::Vector2f NPCTarget = sf::Vector2f(500.0f,500.0f);


	//Font loading
	sf::Font mainFont;
	if (!mainFont.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf"))
	{
		std::cerr << "ERROR: Cannot load font\n";
	}
	//Setup FPS indicator
	sf::Text FPS;
	FPS.setFont(mainFont);
	sf::Clock clock; //FPS clock

	//Setup chat object
	TextBox testText;
	testText.setMargin(35);
	testText.setView(view);

	//Setup tileset
	TileSet light(".\\textures\\test_tileset4.png", { 16,16 });
	TileSet dark(".\\textures\\test_tileset4_dark.png", { 16,16 });
	

	//Setup level
	Level level;
	level.setScale(sf::Vector2f(4, 4));
	level.setTileset(light);
	mp::parseMap(".\\maps\\demo_event-type.mMap", level);
	level.update();

	//Spawn all obj in level
	std::vector<solidObj> solids;
	std::vector<triggerObj> triggers;
	for (int i = 0; i < level.objData.size(); i++)
	{
		if (level.objData[i].type == "solid")
		{
			solids.push_back(solidObj(level.objData[i].pos, level.objData[i].size, 4.0f, false));
		}
		if (level.objData[i].type == "event")
		{
			triggers.push_back(triggerObj(&testEvent, level.objData[i].event_id, level.objData[i].event_type, level.objData[i].pos, level.objData[i].size, 4.0f));
		}
		if (level.objData[i].type == "player_spawn") Player.setPos({ level.objData[i].pos.x*4 , level.objData[i].pos.y *4 });
		if (level.objData[i].type == "green_spawn") Green.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
		if (level.objData[i].type == "red_spawn") Red.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
		if (level.objData[i].type == "koi_spawn") Koy.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
		if (level.objData[i].type == "ghost_spawn") ghostPos = { level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 };
	}

	//Game loop
	while (window.isOpen())
	{
		mousePosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))); //Update global mouse pos
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				resizeView(window, view);
				break;

			case sf::Event::KeyPressed: //Keyboard interfaces
				if (evnt.key.code == sf::Keyboard::Escape) window.close();
				if (evnt.key.code == sf::Keyboard::P) gamePause = !gamePause;

				//chat system related
				if (evnt.key.code == sf::Keyboard::Space)
				{
					testText.Continue();
					testText.updatePosition();
				}
				if (evnt.key.code == sf::Keyboard::F1) testEvent.triggerEvent("chat1");
				if (evnt.key.code == sf::Keyboard::F2) testEvent.triggerEvent("chat2");
				break;

			case sf::Event::MouseButtonPressed:
				if (evnt.key.code == sf::Mouse::Left)
				{
					testText.Continue();
					testText.updatePosition();
				}
				break;

			case sf::Event::MouseWheelScrolled:

				break;
			}
		}
		//Timestep control
		timestep.addFrame();

		//Collision for triggers
		for (int i = 0; i < triggers.size(); i++)
		{
			triggers[i].collide(Player);
		}

		//Chat event handle

		if (testEvent.checkEvent("chat1") && !testText.isDisplay)
		{
			npcFormat = front_line;
			Player.moveDir({ 0,0 });
			testText.addDialogue(TextDiaglogue("แดง", "เอาล่ะ มาเริ่มกันเลย", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "เราขออัญเชิญดวงวิญญาณ ณ ที่แห่งนี้มาสิงสถิตในรูปบานนี้ด้วยเถิด", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "ไม่มีอะไรเกิดขึ้นเลยวะ สงสัยผีแม่งกลัวเราว่ะ  5555", mainFont));
			testText.addDialogue(TextDiaglogue("เขียว", "โถ่น่าเสียดายว่ะ ผีแม่งไม่มีอยู่จริงแน่ๆเลย 55555", mainFont));
			testText.isDisplay = true;
			testText.Continue();
			testText.updatePosition();
		}
		if (testEvent.checkEvent("chat2") && !testText.isDisplay)
		{
			npcFormat = front_line;
			Player.moveDir({ 0,0 });
			testText.addDialogue(TextDiaglogue("ก้อย", "โอ้พระเจ้าดูนั่นสิ!!!\nรูปนั่นมันมีเลือดไหลออกมาด้วยย!!!", mainFont));
			testText.addDialogue(TextDiaglogue("เขียว", "เธอจะบ้ารึไงก้อย\nเธอตาฝาดไปเองรึเปล่า มันจะเป็นไปได้อย่างไง", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "หึหึ พวกนายน่ะคิดไปเองทั้งนั้นแหละ บ้านหลังนี้ไม่เห็นจะมีอะไรเลย", mainFont));
			testText.addDialogue(TextDiaglogue("เอ", "แต่ฉันว่ารูปนั่นเหมือนกับว่ามันขยับได้เลยนะ", mainFont));
			testText.isDisplay = true;
			testText.Continue();
			testText.updatePosition();
		}

		gamePause = testText.isDisplay; //Pause game when chat is being displayed

		//Game pausing
		if (gamePause) timestep.pause();
		else timestep.unpause();

		//Timestep loop
		while (timestep.isUpdateRequired())
		{
			view.setCenter(view.getCenter() + (Player.getPos() - view.getCenter()) / 10.0f);

			//Player controls
			bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				Player.isAuto = true;
				Player.moveTo(mousePosition);
				Player.walkingAnimateAuto();
			}
			else
			{
				Player.isAuto = false;
				Player.control(Right, Left, Down, Up, Sprint);
				Player.walkingAnimate(Right - Left, Down - Up, Player.isSprinting ? 12 : 6);
			}

			if (Player.getSpd().x != 0 || Player.getSpd().y) npcFormat = follow_line;

			//Player solids collision
			for (int i = 0; i < solids.size(); i++)
			{
				solids[i].collide(Player);
				//for (int j = 0; j < NPCs.size(); j++) solids[i].collide(*NPCs[j]); //NPCs collision
		
			}

			//Ghost chasing
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
			{
				Ghost.chase(ghostPos, { 0,400 }, Player);
			}

			//NPCs moving
			npcsMove(NPCs, Player, npcFormat);

			//Update chat position
			testText.updatePosition();

			
		}

		//FPS Debugging
		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+
						"\ndeltaTime: "+std::to_string(deltaTime)+
						"\n mouseX: "+std::to_string(mousePosition.x)+
						"\n mouseY: "+std::to_string(mousePosition.y));
		FPS.setPosition(getViewOffset(view));
		deltaTime = clock.getElapsedTime().asSeconds();
		deltaTime = 1.0f;
		clock.restart(); //Reset FPS clock

		//Rendering
		window.clear();

		window.setView(view);

		level.draw(window);

		for (int i = 0; i < NPCs.size(); i++) NPCs[i]->draw(window); //Draw NPCs

		Player.draw(window);
		Player.drawStamina(window);

		Ghost.draw(window);
		//Ghost.drawDist(window);

		testText.draw(window);
		
		window.draw(FPS);

		window.display();
	}

	return 0;
}

//Functions definition

void resizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(sf::Vector2f(float(WindowHeight)*aspectRatio, float(WindowHeight)));
}



void npcsMove(std::vector<Npc*> &NPCs, Player &Player, npcFormation format)
{
	for (int i = 0; i < NPCs.size(); i++)
	{
		if (format == front_line)
		{
			NPCs[i]->setVisibility(true);
			NPCs[i]->moveTo(Player.getPos() + sf::Vector2f(-120 + (120 * i), -150));
		}
		if (format == back_line)
		{
			NPCs[i]->setVisibility(true);
			NPCs[i]->moveTo(Player.getPos() + sf::Vector2f(-120 + (120 * i), 150));
		}
		if (format == follow_line)
		{
			if (NPCs[i]->moveTo(Player.getPos())) { NPCs[i]->setVisibility(false); }
			if (CUt::dist(NPCs[i]->getPos(), Player.getPos()) > 500)
			{
				NPCs[i]->setPos(Player.getPos());
			}
		}
		NPCs[i]->walkingAnimate();
	}
}