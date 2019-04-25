#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions
#include "Kairos/Timestep.hpp"
#include "Kairos/Timer.hpp"
#include "SFML/Audio.hpp"

#include "door.h"

#include "player.h"
#include "npc.h"
#include "ghost.h"
#include "text_box.h"
#include "tilemap.h"
#include "solid_obj.h"
#include "trigger_obj.h"
#include "map_parser.h"

//Global Variables
enum npcFormation
{
	front_line = 0,
	back_line = 1,
	follow_line = 2
};
sf::Vector2f mousePosition = { 0,0 }, ghostPos = { 0,0 }, viewTarget = { 0,0 }, curViewTarget = { 0,0 };
npcFormation npcFormat = back_line;

float viewCoeffDefault = 10.0f;

float viewCoeff = viewCoeffDefault;
float curViewCoeff = viewCoeffDefault;

bool isDark = false;
bool isDarker = true;
bool showDeath = false;

//Functions prototype
void resizeView(const sf::RenderWindow &, sf::View &);
void retargetView(sf::Vector2f, Player &, float, bool);
void npcsMove(std::vector<Npc*> &, Player &, npcFormation);





int main()
	{
	//Create windows and view
	sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WindowWidth, WindowHeight));
	//sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha");
	window.setVerticalSyncEnabled(true);

	//Create timestep object
	kairos::Timestep timestep;
	kairos::Duration defaultTimer;
	defaultTimer.setFromSeconds(1);
	kairos::Timer timer;
	timer.setTime(defaultTimer);

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

	//Dark overlay
	sf::Texture darkOverlay;
	darkOverlay.loadFromFile(".\\textures\\dark_overlay.png");
	sf::RectangleShape rectDark;
	rectDark.setTexture(&darkOverlay);
	rectDark.setSize(sf::Vector2f(WindowWidth, WindowHeight));

	//semi-dark overlay
	sf::Texture semidarkOverlay;
	semidarkOverlay.loadFromFile(".\\textures\\semi_dark_overlay.png");
	sf::RectangleShape rectsemiDark;
	rectsemiDark.setTexture(&semidarkOverlay);
	rectsemiDark.setSize(sf::Vector2f(WindowWidth, WindowHeight));

	//Normal overlay
	sf::Texture normalOverlay;
	normalOverlay.loadFromFile(".\\textures\\normal_overlay.png");
	sf::RectangleShape rectNormal;
	rectNormal.setTexture(&normalOverlay);
	rectNormal.setSize(sf::Vector2f(WindowWidth, WindowHeight));
	
	//Black rect
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(WindowWidth, WindowHeight));


	//Sound
	sf::SoundBuffer spooky,switc,scream;
	spooky.loadFromFile(".//sounds//spooky.wav");
	switc.loadFromFile(".//sounds//switch.wav");
	scream.loadFromFile(".//sounds//scream1.wav");
	
	sf::Sound sound,sound2;
	sound.setLoop(false);
	sound.setBuffer(spooky);
	sound2.setLoop(false);
	sound2.setBuffer(switc);

	sf::Music music_children;
	music_children.openFromFile(".//sounds//children_room.wav");
	music_children.setLoop(true);
	music_children.play();

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
	testText.setMargin(60);
	testText.setView(view);

	//Setup tileset
	TileSet light(".\\textures\\test_tileset4.png", { 16,16 });
	TileSet dark(".\\textures\\test_tileset4_dark.png", { 16,16 });
	

	//Setup level
	Level level;
	level.setScale(sf::Vector2f(4, 4));
	level.setTileset(light);
	mp::parseMap(".\\maps\\demo.mMap", level);
	level.update();

	//Spawn all obj in level
	std::vector<solidObj> solids;
	std::vector<triggerObj> triggers;
	std::vector<Door> doors;
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
		if (level.objData[i].type == "door")
		{
			doors.push_back(Door(level.objData[i].pos, level.objData[i].size, level.objData[i].event_id, 4.0f));
		}
		if (level.objData[i].type == "player_spawn") Player.setPos({ level.objData[i].pos.x*4 , level.objData[i].pos.y *4 });
		if (level.objData[i].type == "green_spawn") Green.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
		if (level.objData[i].type == "red_spawn") Red.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
		if (level.objData[i].type == "koy_spawn") Koy.setPos({ level.objData[i].pos.x * 4 , level.objData[i].pos.y * 4 });
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

		//Update for doors
		for (int i = 0; i < doors.size(); i++)
		{
			doors[i].update(testEvent, Player);
		}

		//Other event
		if (testEvent.checkEvent("die"))
		{
			kairos::Duration wait;
			wait.setFromSeconds(2);
			timer.setTime(wait);
			timer.start();
			sound.stop();
			showDeath = true;
			if (sound.getStatus() != sf::SoundSource::Status::Playing)
			{
				sound.resetBuffer();
				sound.setBuffer(scream);
				sound.play();
			}
		}

		//Chat event handle

		if (testEvent.checkEvent("chat1") && !testText.isDisplay)
		{
			npcFormat = front_line;
			curViewTarget = Player.getPos();
			curViewCoeff = viewCoeffDefault;
			Player.moveDir({ 0,0 });
			testText.addDialogue(TextDiaglogue("แดง", "เอาล่ะ มาเริ่มกันเลย", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "เราขออัญเชิญดวงวิญญาณ ณ ที่แห่งนี้\nออกมาให้เราสัมผัส ให้เราได้รับรู้ด้วยเถิดด", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "ไม่มีอะไรเกิดขึ้นเลยวะ สงสัยผีแม่งกลัวเราว่ะ  5555", mainFont));
			testText.addDialogue(TextDiaglogue("เขียว", "โถ่น่าเสียดายว่ะ ผีแม่งไม่มีอยู่จริงแน่ๆเลย 55555", mainFont));
			testText.isDisplay = true;
			testText.Continue();
			testText.updatePosition();
		}
		if (testEvent.checkEvent("chat2") && !testText.isDisplay)
		{
			npcFormat = front_line;
			curViewTarget = sf::Vector2f(36 * (4 * 4 * 4), 6 * (4 * 4 * 4)); //Points view to picture
			curViewCoeff = 150.0f; //Slow down view
			Player.moveDir({ 0,0 });
			testText.addDialogue(TextDiaglogue("ก้อย", "โอ้พระเจ้าดูนั่นสิ!!!\nรูปนั่นมันมีเลือดไหลออกมาด้วยย!!!", mainFont));
			testText.addDialogue(TextDiaglogue("เขียว", "เธอจะบ้ารึไงก้อย\nนั่นมันก็แค่คลาบโคลนแหละน่า คิดมากไปได้", mainFont));
			testText.addDialogue(TextDiaglogue("แดง", "หึหึ พวกนายน่ะคิดไปเองทั้งนั้นแหละ บ้านหลังนี้ไม่เห็นจะมีอะไรเลย\nฉันว่าเรากลับกันเถอะ", mainFont));
			testText.addDialogue(TextDiaglogue("เอ", "เดี๋ยวก่อนนะ\nฉันว่ารูปนั่นเหมือนกับว่ามันขยับได้เลยนะ", mainFont));
			testText.isDisplay = true;
			testText.Continue();
			testText.updatePosition();

		}

		if(!testText.isDisplay)
		{
			if (testEvent.checkTriggeredEvent("chat2")) //Run once
			{
				kairos::Duration duration;
				duration.setFromSeconds(0.77);
				timer.setTime(duration);
				timer.start();
				music_children.stop();
				sound2.play();
			}
			
		}

		gamePause = testText.isDisplay; //Pause game when chat is being displayed


		//Manage view target
		retargetView(curViewTarget, Player, curViewCoeff, testText.isDisplay);

		//Timestep loop
		while (timestep.isUpdateRequired())
		{
			view.setCenter(view.getCenter() + (viewTarget - view.getCenter()) / viewCoeff);
			if (isDark)
			{
				rectDark.setPosition(getViewOffset(view));
				rectsemiDark.setPosition(getViewOffset(view));
				if ((rand() % 101) <= 5) isDarker = true;
				else isDarker = false;
			}
			
			rectNormal.setPosition(getViewOffset(view));
			rect.setPosition(getViewOffset(view));
			
			
			//Pausable
			if (!gamePause)
			{
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

				//if (Player.getSpd().x != 0 || Player.getSpd().y) npcFormat = follow_line;

				//Player solids collision
				for (int i = 0; i < solids.size(); i++)
				{
					solids[i].collide(Player);
					//for (int j = 0; j < NPCs.size(); j++) solids[i].collide(*NPCs[j]); //NPCs collision

				}
			}

			//Ghost chasing
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
			if (timer.isDone())
			{
				if (Ghost.chase(ghostPos, { 0,200 }, Player) == 2)
				{
					testEvent.triggerEvent("die");
				}
				isDark = true;
				if (sound.getStatus() != sf::SoundSource::Status::Playing)
				{
					sound.play();
				}
				if (testEvent.checkTriggeredEvent("die")) //Run once
				{
					window.close();
				}
			}

			//NPCs moving
			npcsMove(NPCs, Player, npcFormat);

			//Update chat position
			testText.updatePosition();

			
		}

		//FPS Debugging
		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+
						"\ndeltaTime: "+std::to_string(deltaTime)+
						"\nmouseX: "+std::to_string(mousePosition.x)+
						"\nmouseY: "+std::to_string(mousePosition.y)+
						"\n\ntimer: "+std::to_string(timer.getTime().asSeconds())+
						"\ntimerDone: "+std::to_string(timer.isDone())+
						"\nisDark: "+std::to_string(isDark)+
						"\n\nLastestEvent: "+testEvent.getLastEvent());
		FPS.setPosition(getViewOffset(view));
		deltaTime = clock.getElapsedTime().asSeconds();
		deltaTime = 1.0f;
		clock.restart(); //Reset FPS clock

		//Rendering
		window.clear();

		window.setView(view);

		level.draw(window);

		//draw doors
		for (int i = 0; i < doors.size(); i++)
		{
			doors[i].draw(window);
		}


		for (int i = 0; i < NPCs.size(); i++) NPCs[i]->draw(window); //Draw NPCs

		Player.draw(window);
		Player.drawStamina(window);

		Ghost.draw(window);
		//Ghost.drawDist(window);

		if (isDark) {
			if(isDarker) window.draw(rectsemiDark, sf::BlendMultiply);
			else window.draw(rectDark, sf::BlendMultiply);
		}
		else window.draw(rectNormal, sf::BlendMultiply);

		if (showDeath) window.draw(rect);

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

void retargetView(sf::Vector2f target, Player &Player, float coeff = viewCoeffDefault, bool active = false)
{
	if (active)
	{
		viewTarget = target;
		viewCoeff = coeff;
	}
	else
	{
		viewTarget = Player.getPos();
		viewCoeff = viewCoeffDefault;
	}
}