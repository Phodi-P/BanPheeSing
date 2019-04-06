#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"

class Player
{
public:
	Player(std::string);

	void setPos(float, float);
	sf::Vector2f getPos();

	void draw(sf::RenderWindow &);
	void control(bool, bool, bool, bool);
private:
	sf::Sprite obj;
	sf::Texture t;

	std::string name = "A";

	float speed = 5.0f;
};

Player::Player(std::string ImgDir = " ")
{
	if (!t.loadFromFile(ImgDir))
	{
		std::cerr << "Error: Cannot find player's texture\n";
	}
	obj.setTexture(t);
}

void Player::setPos(float x, float y)
{
	obj.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Player::getPos()
{
	return obj.getPosition();
}

void Player::draw(sf::RenderWindow &window)
{
	window.draw(obj);
}

void Player::control(bool Right, bool Left, bool Down, bool Up)
{
	float xMovement = float(Right - Left);
	float yMovement = float(Down - Up);

	obj.move(sf::Vector2f(xMovement*speed, yMovement*speed));
}