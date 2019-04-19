
#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "custom_utility.h" //This header contain CUt namespace for frequently used utility functions

#include "player.h"
#include "npc.h"
#include "tilemap.h"

const std::string tilesetPath = ".\\textures\\test_tileset.png";
const sf::Vector2u tilesetSize = sf::Vector2u(32, 132);
const unsigned int tilesetRow = 1;
const unsigned int tilesetCol = 4;

int maxTileIdx = (tilesetCol*tilesetRow) - 1;

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

	Obj tilePreview;
	tilePreview.setupAnim(tilesetPath, tilesetSize.x, tilesetSize.y, 16, 16);
	tilePreview.setScale(4.0f, 4.0f);
	tilePreview.getObj().setFillColor(sf::Color(255, 255, 255, 0));
	

	//Font loading
	sf::Font mainFont;
	if (!mainFont.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf"))
	{
		std::cerr << "ERROR: Cannot load font\n";
	}

	sf::Text FPS;
	FPS.setFont(mainFont);


	// define the level with an array of tile indices
	/*const*/ int level[] =
	{
		0, 1, 2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		2, 3, 0, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		0, 1, 2, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};

	TileMap map;
	map.load(tilesetPath, sf::Vector2u(32, 32), level, 16, 8);
	map.setScale(sf::Vector2f(4, 4));

	sf::Clock clock;

	int selectedTileset = 0;
	int pos,posX,posY;
	sf::Vector2f mousePosition;
	sf::Vector2i startRect,endRect;
	startRect.x = -1, startRect.y = -1;
	endRect.x = -1, endRect.y = -1;
	bool isRected = false;

	

	std::ofstream fwrite;

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
				switch (evnt.key.code) {
				case sf::Keyboard::Num0:
					selectedTileset = 0;
					break;

				case sf::Keyboard::Num1:
					selectedTileset = 1;
					break;

				case sf::Keyboard::Num2:
					selectedTileset = 2;
					break;

				case sf::Keyboard::Num3:
					selectedTileset = 3;
					break;

				case sf::Keyboard::R:
					isRected = !isRected;
					break;
				//Print selectedTileset
				/*case sf::Keyboard::P:
					std::cout << selectedTileset << std::endl;
					break;*/
				case sf::Keyboard::P:
					fwrite.open(".\\maps\\test_map.txt");
					fwrite << 8 << std::endl << 16 << std::endl;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 16; j++) fwrite << level[(i * 16) + j];
						fwrite << std::endl;
					} 
					fwrite.close();
					break;
				}

				break;
			case sf::Event::MouseButtonPressed:
				//When mouse button is Pressed
				posX = (int)((mousePosition.x / 4) / 32);
				posY = (int)((mousePosition.y / 4) / 32);
				pos = (posY * 16) + posX;
				if (isRected) {
					if (startRect.x == -1 && startRect.y == -1) {
						startRect.x = posX;
						startRect.y = posY;
					}
					else if (endRect.x == -1 && endRect.y == -1) {
						endRect.x = posX;
						endRect.y = posY;

						for (int i = startRect.y; i <= endRect.y; i++) for (int j = startRect.x; j <= endRect.x; j++) level[(i * 16) + j] = selectedTileset;
						map.load(tilesetPath, sf::Vector2u(32, 32), level, 16, 8);
						startRect.x = -1;
						startRect.y = -1;
						endRect.x = -1;
						endRect.y = -1;
					}
					break;
				}
				// Debug map position
				//std::cout << level[pos] << std::endl;
				//std::cout << (int)(mousePosition.y / 32) << " " << (int)(mousePosition.x / 32) << std::endl;
				//
				level[pos] = selectedTileset;
				map.load(tilesetPath, sf::Vector2u(32, 32), level, 16, 8);
				break;

			case sf::Event::MouseWheelScrolled:
				selectedTileset += CUt::sign(evnt.mouseWheelScroll.delta);
				//if (selectedTileset >= (tilesetRow*tilesetCol)) selectedTileset = 0;
				if (selectedTileset > maxTileIdx) selectedTileset = 0;
				if (selectedTileset < 0) selectedTileset = maxTileIdx;
				break;

			case sf::Event::MouseMoved:
				break;
			}
		}
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		view.setCenter(view.getCenter() + (Player.getPos() - view.getCenter()) / 10.0f);

		//Player controls
		bool Right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		bool Left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool Sprint = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

		Player.control(Right, Left, Down, Up, Sprint, deltaTime);
		Player.walkingAnimate(Right-Left,Down-Up,Player.isSprinting ? 12 : 6);

		tilePreview.animate(selectedTileset, 0);
		tilePreview.setPos(mousePosition);


		//FPS and deltaTime
		FPS.setString("FPS: "+std::to_string(1.0f / clock.getElapsedTime().asSeconds())+"\ndeltaTime: "+std::to_string(deltaTime)+"\nselectedTile: "+std::to_string(selectedTileset));
		FPS.setPosition(getViewOffset(view));
		clock.restart();

		//Rendering
		window.clear();
		
		window.draw(map);
		window.setView(view);
		Player.draw(window);
		tilePreview.draw(window);

		window.draw(FPS);

		window.display();
	}

	return 0;
}