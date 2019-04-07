#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"
#include <vector>


class Obj
{
public:

	Obj();
	~Obj();

	void pushToVector(std::vector<Obj*> *);

	void setPos(sf::Vector2f);
	sf::Vector2f getPos();

	sf::Sprite getObj();

	void setTexture(std::string, sf::IntRect);
	void setScale(float, float);

	void moveTo(sf::Vector2f);

	void draw(sf::RenderWindow &);


protected:

	float speed = 1.0f;
	int id;
	bool isMoving = false;

	float scaleX = 1.0f;
	float scaleY = 1.0f;

	sf::Sprite obj;
	sf::Texture texture;

	std::vector<Obj*> *ObjList = NULL;
};

Obj::Obj()
{
	//Default
}

sf::Sprite Obj::getObj()
{
	return obj;
}

Obj::~Obj()
{
	(*ObjList).erase((*ObjList).begin() + id);
}

void Obj::setPos(sf::Vector2f pos)
{
	obj.setPosition(pos);
}

sf::Vector2f Obj::getPos()
{
	return obj.getPosition();
}

void Obj::draw(sf::RenderWindow &window)
{
	window.draw(obj);
}

void Obj::moveTo(sf::Vector2f dest)
{
	if (dest != getPos())
	{
		isMoving = true;

		float xMovement = float(CUt::sign(dest.x - getPos().x));
		float yMovement = float(CUt::sign(dest.y - getPos().y));

		obj.move(sf::Vector2f(xMovement*speed, yMovement*speed));
	}
	if (dest == getPos())
	{
		isMoving = false;
	}
}

void Obj::setScale(float x, float y)
{
	scaleX = x;
	scaleY = y;
}

void Obj::setTexture(std::string ImgDir, sf::IntRect rect = sf::IntRect(0,0,0,0))
{
	if (!texture.loadFromFile(ImgDir, rect))
	{
		std::cerr << "Error: Cannot find player's texture\n";

		texture.loadFromFile(".\\textures\\missing_error.png");
	}
	obj.setTexture(texture);
	obj.setScale(scaleX, scaleY);
}