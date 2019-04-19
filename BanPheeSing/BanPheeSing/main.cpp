
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"
#include "tilemap.h"

void resizeView(const sf::RenderWindow &window, sf::View &view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(sf::Vector2f(float(WindowHeight)*aspectRatio, float(WindowHeight)));
}

int main()
	{
	//sf::RenderWindow window(sf::VideoMode(RoomWidth, RoomHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WindowWidth, WindowHeight));
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha");

	//Create Objects here
	Player Player(".\\textures\\a_sprite.png",32,32,4,3);
	Player.setScale(4.0f, 4.0f);



	//Font loading
	sf::Font mainFont;
	if (!mainFont.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf"))
	{
		std::cerr << "ERROR: Cannot load font\n";
	}

	sf::Text FPS;
	FPS.setFont(mainFont);


	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	TileMap map;
	map.load(".\\textures\\test_tileset.png", sf::Vector2u(32, 32), level, 16, 8);
	map.setScale(sf::Vector2f(4, 4));

	sf::Clock clock;

	while (window.isOpen())
	{
		float deltaTime = clock.getElapsedTime().asSeconds();
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
				//When mouse button is Pressed
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

		Player.control(Right, Left, Down, Up, Sprint, deltaTime);
		Player.walkingAnimate(Right-Left,Down-Up,Player.isSprinting ? 12 : 6);



		//FPS and deltaTime
		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+"\ndeltaTime: "+std::to_string(deltaTime));
		FPS.setPosition(getViewOffset(view));
		clock.restart();

		//Rendering
		window.clear();

		window.draw(map);
		window.setView(view);
		Player.draw(window);

		window.draw(FPS);

		window.display();
	}

	return 0;
}