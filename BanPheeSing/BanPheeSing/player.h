#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(float, float, float);
	void setPos(float, float);
	void draw(sf::RenderWindow &);
	void control(bool, bool, bool, bool);
private:
	sf::CircleShape obj;

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