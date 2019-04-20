
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"
#include "ghost.h"
#include "text_box.h"
#include "tilemap.h"

void resizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(sf::Vector2f(float(WindowHeight)*aspectRatio, float(WindowHeight)));
}


//Global Variables
std::vector<Obj*> allObjPtr;
sf::Vector2f mousePosition = { 0,0 };


int main()
	{
	sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WindowWidth, WindowHeight));
	//sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha");

	//Create Objects here
	Player Player(".\\textures\\a_sprite.png",32,32,4,3);
	Player.setScale(4.0f, 4.0f);

	Ghost Ghost(sf::Vector2f(0.0f,0.0f), ".\\textures\\ghost_sprite.png",96 ,192 ,4 ,3);
	Ghost.setScale(1.0f, 1.0f);
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
	testText.setView(view);
	testText.isDisplay = true;
	//testText.addDialogue(TextDiaglogue("Claudette", "Oh shit!!!\nHe saw me!!!", ".//textures//test_portrait.png", mainFont, sf::Color::Magenta));
	//testText.addDialogue(TextDiaglogue("Some random guy", "Don't worry\nI'll help you.", ".//textures//test_portrait2.png", mainFont, sf::Color::Black));
	//testText.addDialogue(TextDiaglogue("Claudette", "Run you fool!!!", ".//textures//test_portrait.png", mainFont, sf::Color::Magenta));
	
	TileSet light(".\\textures\\test_tileset4.png", { 16,16 });
	TileSet dark(".\\textures\\test_tileset4_dark.png", { 16,16 });
	
	Level level;
	level.setScale(sf::Vector2f(4, 4));
	level.setTileset(light);
	level.readFile(".\\maps\\demo_bot.txt", ".\\maps\\demo_mid.txt", ".\\maps\\demo_top.txt");
	level.update();


	sf::Clock clock;

	while (window.isOpen())
	{
		mousePosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		deltaTime = clock.getElapsedTime().asSeconds();
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
				break;
			case sf::Event::MouseButtonPressed:
				//Ghost.vec_moveToQueue.push_back(NPCTarget);
				testText.Continue();
			case sf::Event::MouseWheelScrolled:
				break;
			}
		}

		view.setCenter(view.getCenter() + (Player.getPos() - view.getCenter()) / 10.0f);

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		Player.control(Right, Left, Down, Up, Sprint);
		Player.walkingAnimate(Right-Left,Down-Up,Player.isSprinting ? 12 : 6);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Ghost.chase({ 1024,200 }, { 0,400 }, Player);
		}
		//NPC test
		//Ghost.moveToQueue();
		//Ghost.walkingAnimate();


		testText.updatePosition();

		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+
						"\ndeltaTime: "+std::to_string(deltaTime)+
						"\n mouseX: "+std::to_string(mousePosition.x)+
						"\n mouseY: "+std::to_string(mousePosition.y));
		FPS.setPosition(getViewOffset(view));
		clock.restart();

		//Rendering
		window.clear();

		level.draw(window);
		window.setView(view);
		Player.draw(window);
		Player.drawStamina(window);
		Ghost.draw(window);
		testText.draw(window);
		Ghost.drawDist(window);

		window.draw(FPS);

		window.display();
	}

	return 0;
}