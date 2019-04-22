#pragma once
#include"custom_utility.h"

class Button
{
	std::string btnName;
	std::string btnType;
	sf::Vector2f btnPosition;
	sf::Vector2f btnSize;
public:
	Button(std::string);
	void create(sf::RenderWindow &);
};

Button::Button(std::string name,sf) {
	btnName = name;
}

void Button::create(sf::RenderWindow &window) {
	sf::RectangleShape btn;
	btn.setSize(btnSize);
	btn.setFillColor(sf::Color(2, 2, 2));
	btn.setPosition(btnPosition);
	window.draw(btn);
}

