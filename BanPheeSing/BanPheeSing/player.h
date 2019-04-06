#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"

class Player
{
public:
	Player(float, float, float);
	void setPos(float, float);
	sf::Vector2f getPos();
	void draw(sf::RenderWindow &);
	void control(bool, bool, bool, bool);
private:
	sf::CircleShape obj;

	std::string name = "A";
	float speed = 5.0f;
};

Player::Player(float InitX = 0.0f, float InitY = 0.0f, float InitR = 10.0f)
{
	obj.setRadius(InitR);
	obj.setFillColor(sf::Color::Green);
	obj.setPosition(sf::Vector2f(InitX, InitY));
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