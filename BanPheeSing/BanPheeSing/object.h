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

	void setTexture(std::string);

	void moveTo(sf::Vector2f);

	void draw(sf::RenderWindow &);


protected:

	float speed = 1.0f;
	int id;

	sf::Sprite obj;
	sf::Texture texture;

	std::vector<Obj*> *ObjList = NULL;
};

Obj::Obj()
{
	//Default
}

void Obj::pushToVector(std::vector<Obj*> *inputList)
{
	ObjList = inputList;
	if (ObjList != NULL)
	{
		//Store object pointer to global vector
		(*ObjList).push_back(this);

		//Save object index
		id = (*ObjList).size() - 1;
	}
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
	float xMovement = float(CUt::sign(dest.x - getPos().x));
	float yMovement = float(CUt::sign(dest.y - getPos().y));

	obj.move(sf::Vector2f(xMovement*speed, yMovement*speed));
}

void Obj::setTexture(std::string ImgDir)
{
	if (!texture.loadFromFile(ImgDir))
	{
		std::cerr << "Error: Cannot find player's texture\n";

		texture.loadFromFile(".\\textures\\missing_error.png");
	}
	obj.setTexture(texture);
}