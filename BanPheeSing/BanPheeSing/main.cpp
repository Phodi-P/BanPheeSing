
#include <iostream>
#include <SFML/Graphics.hpp>

#include "custom_utility.h"

#include "player.h"
#include "npc.h"

//Settings
const int WindowWidth = 1920;
const int WindowHeight = 1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	/*
	sf::CircleShape shape(10.f); //Example shape
	shape.setFillColor(sf::Color::Green); //Example shape*/
	Player Player;
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

		Player.control(sf::Keyboard::isKeyPressed(sf::Keyboard::D), sf::Keyboard::isKeyPressed(sf::Keyboard::A), sf::Keyboard::isKeyPressed(sf::Keyboard::S), sf::Keyboard::isKeyPressed(sf::Keyboard::W));
		Npc1.moveTo(sf::Vector2f(600.0f, 600.0f));

		window.clear();
		//window.draw(shape); //Example shape
		Player.draw(window);
		Npc1.draw(window);
		window.display();
	}

	return 0;
}