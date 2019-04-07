
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"

//Settings
const int WindowWidth = 1920*0.5;
const int WindowHeight = 1080*0.5;


//Global Variables
std::vector<Obj*> allObjPtr;

int main()
	{
	//sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha");
	//Create Objects here
	Player Player(".\\textures\\test_sprite.png",32,32,4,3);
	Player.setScale(2.0f, 2.0f);
	//Npc Npc1({ 20,0 }, ".\\textures\\gurumaa.jpg", "B");

	std::cout << "Test\n";
	for (int i = 0; i < allObjPtr.size(); i++)
	{
		std::cout << "There are " << i << " objects in global list\n";
	}
	
	int tarFrame = 0;

	std::cout << "Current frame is " << tarFrame << std::endl;

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
				if (evnt.key.code == sf::Keyboard::D) Player.animate(6, 0);
				if (evnt.key.code == sf::Keyboard::A) Player.animate(3, 0);
				if (evnt.key.code == sf::Keyboard::W) Player.animate(9, 0);
				if (evnt.key.code == sf::Keyboard::S) Player.animate(0, 0);

				break;
			case sf::Event::MouseLeft:
				tarFrame++;
				if (tarFrame > (3 * 4)-1) tarFrame = 0;


				break;
			}
		}

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);

		Player.control(Right, Left, Down, Up);
		Player.walkingAnimate(Right-Left,Down-Up,4);
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