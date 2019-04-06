
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"

//Settings
const int WindowWidth = 1920;
const int WindowHeight = 1080;


//Global Variables
std::vector<Obj*> allObjPtr;

int main()
	{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);

	//Create Objects here
	Player Player(".\\textures\\gurumaa.jpg", &allObjPtr);
	//Npc Npc1({ 20,0 }, ".\\textures\\gurumaa.jpg", "B");

	std::cout << "Test\n";
	for (int i = 0; i < allObjPtr.size(); i++)
	{
		std::cout << "There are " << i << " objects in global list\n";
	}

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
			}
		}

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

		Player.control(Right, Left, Down, Up);
		
		//NPC test
		//Npc1.moveTo(sf::Vector2f(700.0f, 700.0f));


		//Rendering
		window.clear();

		Player.draw(window);
		//Npc1.draw(window);

		window.display();
	}

	return 0;
}