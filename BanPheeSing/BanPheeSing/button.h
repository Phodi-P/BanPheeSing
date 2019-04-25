#pragma once
#include"custom_utility.h"
class Button
{
public:
	Button(std::string, std::string, sf::Vector2f, sf::Font &);
	void select();
	void unselect();
	void drawButton(sf::RenderWindow &);

private:
	sf::Text button;
	sf::RectangleShape border;
};

Button::Button(std::string name, std::string id, sf::Vector2f position, sf::Font &font) {
	int fontSize = 72;

	button.setFont(font);
	button.setFillColor(sf::Color::White);
	button.setString(name);

	float bw = button.getGlobalBounds().width+(fontSize / 2);
	float bh = button.getGlobalBounds().height;

	//button.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / (N + 1) * (stoi(id))));
	button.setOrigin(sf::Vector2f(bw / 2, bh / 2));
	button.setPosition(position);
	button.setCharacterSize(fontSize);

	//float w = 200, h = 100;
	//border.setPosition(position.x-(w/4),  position.y-(h/4));
	//border.setSize(sf::Vector2f(w,h));

	border.setSize(sf::Vector2f(bw+100, bh+70));
	border.setOrigin(sf::Vector2f((border.getSize().x / 2 ) +(fontSize / 4), border.getSize().y / 2));

	border.setPosition(position.x + (bw/2), position.y + (bh/2)+(fontSize/2));
	
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