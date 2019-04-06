
#include <iostream>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //Add some frequently used utility functions here

#include "player.h"
#include "npc.h"

//Settings
const int WindowWidth = 1920;
const int WindowHeight = 1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);

	//Create Objects here
	Player Player("gurumaa.jpg");
	Npc Npc1(20,0,10,"B");


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
		
		Npc1.moveTo(sf::Vector2f(700.0f, 700.0f));

		window.clear();

		Player.draw(window);
		Npc1.draw(window);

		window.display();
	}

	return 0;
}