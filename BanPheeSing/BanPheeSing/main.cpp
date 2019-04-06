#include <SFML/Graphics.hpp>

//Settings
const int WindowWidth = 1920;
const int WindowHeight = 1080;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "BanPheeSing: Very Alpha", sf::Style::Fullscreen);
	sf::CircleShape shape(10.f); //Example shape
	shape.setFillColor(sf::Color::Green); //Example shape

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


		window.clear();
		window.draw(shape); //Example shape
		window.display();
	}

	return 0;
}