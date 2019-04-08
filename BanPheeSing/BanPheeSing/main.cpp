
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"

//Settings
const int WindowWidth = 1920/1;
const int WindowHeight = 1080/1;


//Global Variables
std::vector<Obj*> allObjPtr;


int main()
	{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	//sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha");

	//Create Objects here
	Player Player(".\\textures\\a_sprite.png",32,32,4,3);
	Player.setScale(4.0f, 4.0f);

	Npc Npc1(sf::Vector2f(0.0f,0.0f), ".\\textures\\green_sprite.png",32 ,32 ,4 ,3 , "B");
	Npc1.setScale(4.0f, 4.0f);
	sf::Vector2f NPCTarget = sf::Vector2f(500.0f,500.0f);


	//Font loading
	sf::Font mainFont;
	if (!mainFont.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf"))
	{
		std::cerr << "ERROR: Cannot load font\n";
	}

	sf::Text text;

	text.setFont(mainFont); // font is a sf::Font
	text.setString(L"สวัสดี ชาวโลก");
	text.setCharacterSize(24); // in pixels, not points!
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);



	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape) window.close();
				break;
			case sf::Event::MouseButtonPressed:
				NPCTarget = sf::Vector2f(sf::Mouse::getPosition(window));
				Npc1.vec_moveToQueue.push_back(NPCTarget);
				break;
			}
		}

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		Player.control(Right, Left, Down, Up, Sprint);
		Player.walkingAnimate(Right-Left,Down-Up,6);
		//NPC test
		Npc1.moveToQueue();
		Npc1.walkingAnimate();



		//Rendering
		window.clear();

		Player.draw(window);
		Npc1.draw(window);
		window.draw(text);

		window.display();
	}

	return 0;
}