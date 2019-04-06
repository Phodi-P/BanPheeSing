#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"

class Npc
{
public:
	Npc(float, float, float,std::string);

	void setPos(float, float);
	sf::Vector2f getPos();

	void moveTo(sf::Vector2f);

	void draw(sf::RenderWindow &);
private:
	sf::CircleShape obj;
	//CUt CUt;

	std::string name;
	float speed = 5.0f;
};

Npc::Npc(float InitX = 0.0f, float InitY = 0.0f, float InitR = 10.0f, std::string n = "NPC")
{
	name = n;
	obj.setRadius(InitR);
	obj.setFillColor(sf::Color::Red);
	obj.setPosition(sf::Vector2f(InitX, InitY));
}

void Npc::setPos(float x, float y)
{
	obj.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Npc::getPos()
{
	return obj.getPosition();
}

void Npc::draw(sf::RenderWindow &window)
{
	window.draw(obj);
}

void Npc::moveTo(sf::Vector2f dest)
{
	//float xMovement = float(CUt.sign(dest.x-getPos().x));
	//float yMovement = float(CUt.sign(dest.y - getPos().y));

	float xMovement = float(CUt::sign(dest.x-getPos().x));
	float yMovement = float(CUt::sign(dest.y - getPos().y));

	obj.move(sf::Vector2f(xMovement*speed, yMovement*speed));
}