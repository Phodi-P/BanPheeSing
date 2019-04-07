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
	//~Obj();


	void setPos(sf::Vector2f);
	sf::Vector2f getPos();

	sf::Sprite getObj();

	void setupAnim(std::string, int , int , int , int);
	int animate(int, int);
	void setMyTexture(sf::Texture &, std::string, sf::IntRect);
	void setScale(float, float);

	void moveTo(sf::Vector2f);

	void draw(sf::RenderWindow &);


protected:

	float speed = 1.0f;
	int id;
	bool isMoving = false;

	float scaleX = 1.0f;
	float scaleY = 1.0f;

	float xSpeed = 0;
	float ySpeed = 0;

	sf::Sprite obj;
	sf::Texture texture;

	//Sprite sheet animation details
	bool isAnimated = false;
	sf::Texture spriteSheet;
	std::string ImgDir;
	sf::Clock animationClock;
	int frameWidth = 32;
	int frameHeight = 32;
	int frameRows = 1;
	int frameColumns = 1;
	int curFrame = 0;


};

Obj::Obj()
{
	//Default
}

sf::Sprite Obj::getObj()
{
	return obj;
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

		if ((std::abs(dest.x - getPos().x) <= 1) && (std::abs(dest.y - getPos().y) <= 1))
		{
			setPos(dest); //Stop when distanct to target is 1
		}

		float xMovement = float(CUt::sign(dest.x - getPos().x));
		float yMovement = float(CUt::sign(dest.y - getPos().y));

		xSpeed = xMovement * speed;
		ySpeed = yMovement * speed;

		
	}
	if (dest == getPos())
	{
		isMoving = false;
	}

	obj.move(sf::Vector2f(xSpeed*((xSpeed!=0 && ySpeed != 0)?0.707:1), ySpeed));
}

void Obj::setScale(float x, float y)
{
	scaleX = x;
	scaleY = y;
}

void Obj::setMyTexture(sf::Texture &TarTexture, std::string ImgDir, sf::IntRect rect = sf::IntRect(0,0,0,0))
{
	if (!isAnimated)
	{
		if (!TarTexture.loadFromFile(ImgDir))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			TarTexture.loadFromFile(".\\textures\\missing_error.png");
		}
	}
	if(isAnimated)
	{
		if (!TarTexture.loadFromFile(ImgDir, rect))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			TarTexture.loadFromFile(".\\textures\\missing_error.png");
		}
	}
	obj.setTexture(TarTexture);
	obj.setScale(scaleX, scaleY);
}

void Obj::setupAnim(std::string ImgDirI, int frameIWidth, int frameIHeight, int frameIRows = 1, int frameIColumns = 1)
{
	isAnimated = true;

	frameWidth = frameIWidth;
	frameHeight = frameIHeight;
	frameRows = frameIRows;
	frameColumns = frameIColumns;

	ImgDir = ImgDirI;

	setMyTexture(spriteSheet,ImgDir, sf::IntRect(0, 0, frameWidth, frameHeight));
}

int Obj::animate(int setFrame = -1, int fps = 1)
{
	if (isAnimated)
	{
		sf::IntRect rect;
		if (setFrame != -1)
		{
			curFrame = setFrame;
		}
		else if (setFrame == -1)
		{
			if (fps > 0 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
			{
				animationClock.restart();
				curFrame++;
			}
			curFrame++;
			if (curFrame > (frameColumns*frameRows) - 1) curFrame = 0;
		}
		int tarRow = std::ceil(curFrame / frameColumns);
		int tarCol = (curFrame % frameColumns);

		rect = sf::IntRect(frameWidth*tarCol, frameHeight*tarRow, (frameWidth*tarCol) + frameWidth, (frameHeight*tarRow) + frameHeight);

		setMyTexture(spriteSheet,ImgDir, rect);

		return curFrame;
	}
	else
	{
		throw("This object is non-animated\n");
	}
}