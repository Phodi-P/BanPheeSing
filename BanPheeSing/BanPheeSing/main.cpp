
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

	Npc Npc1(sf::Vector2f(0.0f,0.0f), ".\\textures\\red_sprite.png", "B");
	Npc1.setScale(4.0f, 4.0f);
	Npc1.setupAnim(".\\textures\\red_sprite.png", 32, 32, 4, 3);


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

				//Imediatly change player sprite dir when press control buttons 
				/*
				if (evnt.key.code == sf::Keyboard::D) Player.animate(6, 0);
				if (evnt.key.code == sf::Keyboard::A) Player.animate(3, 0);
				if (evnt.key.code == sf::Keyboard::W) Player.animate(9, 0);
				if (evnt.key.code == sf::Keyboard::S) Player.animate(0, 0);
				*/
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
		Npc1.moveTo(sf::Vector2f(900.0f, 700.0f));
		Npc1.walkingAnimate();



		//Rendering
		window.clear();

		Player.draw(window);
		Npc1.draw(window);

		window.display();
	}

	return 0;
}