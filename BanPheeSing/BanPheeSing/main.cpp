


#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions
#include "Kairos/Timestep.hpp"
#include "door.h"
#include "player.h"
#include "npc.h"
#include "ghost.h"
#include "text_box.h"
#include "tilemap.h"
#include "solid_obj.h"
#include "map_parser.h"

void resizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(sf::Vector2f(float(WindowHeight)*aspectRatio, float(WindowHeight)));
}


//Global Variables
sf::Vector2f mousePosition = { 0,0 };


int main()
	{
	//Door x(500,500);
	//x.setDoor(true);
	sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WindowWidth, WindowHeight));
	//sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha");
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(30);
	kairos::Timestep timestep;

	//Create Objects here
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

	sf::Text FPS;
	FPS.setFont(mainFont);
	//FPS.setColor(sf::Color::Blue);

	TextBox testText;
	testText.setMargin(35);
	testText.setView(view);
	testText.isDisplay = true;
	testText.addDialogue(TextDiaglogue("ก้อย", "โอ้พระเจ้าดูนั่นสิ!!!\nรูปนั่นมันมีเลือดไหลออกมาด้วยย!!!", ".//textures//portraits//koy.png", mainFont, sf::Color::Magenta));
	testText.addDialogue(TextDiaglogue("เขียว", "เธอจะบ้ารึไงก้อย\nเธอตาฝาดไปเองรึเปล่า มันจะเป็นไปได้อย่างไง", ".//textures//portraits//green.png", mainFont, sf::Color::Green));
	testText.addDialogue(TextDiaglogue("เอิร์ธ", "หึหึ พวกนายน่ะคิดไปเองทั้งนั้นแหละ บ้านหลังนี้ไม่เห็นจะมีอะไรเลย", ".//textures//portraits//red.png", mainFont, sf::Color::Red));
	testText.addDialogue(TextDiaglogue("เจมส์", "แต่ฉันว่ารูปนั่นเหมือนกับว่ามันขยับได้เลยนะ", ".//textures//portraits//a.png", mainFont, sf::Color::Blue));

	
	TileSet light(".\\textures\\test_tileset4.png", { 16,16 });
	TileSet dark(".\\textures\\test_tileset4_dark.png", { 16,16 });
	
	Level level;
	level.setScale(sf::Vector2f(4, 4));
	level.setTileset(light);
	mp::parseMap(".\\maps\\export.mMap", level);
	//level.readFile(".\\maps\\demo_bot.txt", ".\\maps\\demo_mid.txt", ".\\maps\\demo_top.txt");
	level.update();

	//solidObj solid({ 100,0 }, { 50,700 }, true);
	std::cout << level.objData.size();
	std::vector<solidObj> solids;
	for (int i = 0; i < level.objData.size(); i++)
	{
		if (level.objData[i].type == "solid")
		{
			solids.push_back(solidObj(level.objData[i].pos, level.objData[i].size, 4.0f, false));
		}
	}

	sf::Clock clock;

	while (window.isOpen())
	{
		mousePosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
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
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape) window.close();
				if (evnt.key.code == sf::Keyboard::P)
				{
					gamePause = !gamePause;
				}
				break;
			case sf::Event::MouseButtonPressed:
				//Ghost.vec_moveToQueue.push_back(NPCTarget);
				testText.Continue();
				testText.updatePosition();
			case sf::Event::MouseWheelScrolled:
				break;
			}
		}
		timestep.addFrame();
		if (gamePause) timestep.pause();
		else timestep.unpause();

		while (timestep.isUpdateRequired())
		{
			//deltaTime = timestep.getStepAsFloat();
			view.setCenter(view.getCenter() + (Player.getPos() - view.getCenter()) / 10.0f);

			//Player controls
			bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
			bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

			Player.control(Right, Left, Down, Up, Sprint);
			Player.walkingAnimate(Right - Left, Down - Up, Player.isSprinting ? 12 : 6);

			//solid.collide(Player);
			//solid.collide(Ghost);
			for (int i = 0; i < solids.size(); i++)
			{
				solids[i].collide(Player);
				for (int j = 0; j < NPCs.size(); j++)
				{
					solids[i].collide(*NPCs[j]);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				Ghost.chase({ 1024,200 }, { 0,400 }, Player);
			}

			//NPC test
			for (int i = 0; i < NPCs.size(); i++)
			{
				NPCs[i]->moveTo(Player.getPos() + sf::Vector2f(-120 + (120 * i), -150));
				NPCs[i]->walkingAnimate();
			}
			//Ghost.moveToQueue();
			//Ghost.walkingAnimate();
			testText.updatePosition();

			
		}
		

		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+
						"\ndeltaTime: "+std::to_string(deltaTime)+
						"\n mouseX: "+std::to_string(mousePosition.x)+
						"\n mouseY: "+std::to_string(mousePosition.y));
		FPS.setPosition(getViewOffset(view));
		deltaTime = clock.getElapsedTime().asSeconds();
		deltaTime = 1.0f;
		clock.restart();

		//Rendering
		window.clear();

		level.draw(window);
		window.setView(view);

		Red.draw(window);
		Green.draw(window);
		Koy.draw(window);

		Player.draw(window);
		Player.drawStamina(window);

		for (int i = 0; i < NPCs.size(); i++) NPCs[i]->draw(window);

		Ghost.draw(window);
		testText.draw(window);
		Ghost.drawDist(window);

		//window.draw(solid.obj);
		//for (int i = 0; i < solids.size(); i++) window.draw(solids[i].obj);
		//x.draw(window);
		window.draw(FPS);
		window.display();
	}

	return 0;
}