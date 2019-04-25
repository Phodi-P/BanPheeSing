#pragma once
#include"custom_utility.h"
class Button
{
	public:
		Button(std::string,std::string,sf::Vector2f, sf::Font &);
		void select();
		void unselect();
		void drawButton(sf::RenderWindow &);
		
	private: 
		sf::Text button;
		sf::RectangleShape border;
};

Button::Button(std::string name, std::string id, sf::Vector2f position, sf::Font &font) {
	button.setFont(font);
	button.setFillColor(sf::Color::White);
	button.setString(name);
	//button.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / (N + 1) * (stoi(id))));
	button.setPosition(position);
	button.setCharacterSize(72);

	float bw = button.getGlobalBounds().width;
	float bh = button.getGlobalBounds().height;
	//float w = 200, h = 100;
	//border.setPosition(position.x-(w/4),  position.y-(h/4));
	//border.setSize(sf::Vector2f(w,h));

	border.setPosition(position.x - 100, position.y - 100);
	border.setSize(sf::Vector2f(bw + 200, bh + 200));
	border.setFillColor(sf::Color::Black);
}

void Button::select() {
	button.setFillColor(sf::Color::Red);
}

void Button::unselect() {
	button.setFillColor(sf::Color::White);
}

void Button::drawButton(sf::RenderWindow &window) {
	window.draw(border);
	window.draw(button);
}
