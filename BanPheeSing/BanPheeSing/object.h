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
	sf::RectangleShape getObj();

	//Graphic and animation

	void setScale(float, float);

	void setupStatic(std::string);
	void setupAnim(std::string, int , int , int , int);
	void setVisibility(bool);

	int animate(int, int);


	void draw(sf::RenderWindow &);
	
	//Movement

	void setPos(sf::Vector2f);
	sf::Vector2f getPos();
	void setSpd(float);
	sf::Vector2f getSpd();

	void moveDir(sf::Vector2f);

	bool moveTo(sf::Vector2f);
	int moveToQueue();

	int curMoveToQueue = 0;
	std::vector<sf::Vector2f> vec_moveToQueue;

	
protected:
	//Variables
	bool isInitialized = false;
	bool isVisible = true;
	sf::RectangleShape obj;
	sf::Texture texture;

	sf::CircleShape CenterPoint;

	//Movement config

	int id;
	bool isMoving = false;

	float speed = 300.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;

	float xSpeed = 0;
	float ySpeed = 0;



	//Sprite sheet animation details
	bool isAnimated = false;
	std::string ImgDir;
	sf::Clock animationClock;
	int frameWidth = 32;
	int frameHeight = 32;
	int frameRows = 1;
	int frameColumns = 1;
	int curFrame = 0;

	//Functions

	void setMyTexture(std::string, sf::IntRect);

};

Obj::Obj()
{
	//Default
	obj.setSize(sf::Vector2f(32, 32));
	obj.setOrigin(sf::Vector2f(16, 16));
	CenterPoint.setRadius(5.0f);
	CenterPoint.setFillColor(sf::Color::Red);
}

void Obj::setSpd(float spd)
{
	speed = spd;
}

sf::RectangleShape Obj::getObj()
{
	return obj;
}


void Obj::setPos(sf::Vector2f pos)
{
	obj.setPosition(pos);
}

void Obj::setVisibility(bool visible)
{
	isVisible = visible;
}

sf::Vector2f Obj::getPos()
{
	return obj.getPosition();
}

void Obj::draw(sf::RenderWindow &window)
{
	if (isVisible)
	{
		window.draw(obj);
		window.draw(CenterPoint);
	}
}

void Obj::moveDir(sf::Vector2f spd)
{
	xSpeed = spd.x*deltaTime;
	ySpeed = spd.y*deltaTime;

	if (spd.x != 0 && spd.y != 0)
	{
		spd.x *= 0.707;
		spd.y *= 0.707;
	}

	obj.move(spd);
	CenterPoint.setPosition(getPos());

}

sf::Vector2f Obj::getSpd()
{
	return sf::Vector2f(xSpeed, ySpeed);
}

//Move to target destination
//Returns true when target is reached
bool Obj::moveTo(sf::Vector2f dest)
{
	float tempX = 0;
	float tempY = 0;
	if (dest != getPos())
	{
		isMoving = true;

		if ((std::abs(dest.x - getPos().x) <= 1) && (std::abs(dest.y - getPos().y) <= 1))
		{
			setPos(dest); //Stop when distanct to target is 1
			tempX = 0;
			tempY = 0;
		}



		float xMovement = float((dest.x - getPos().x));
		float yMovement = float((dest.y - getPos().y));

		float len = std::sqrt(xMovement*xMovement + yMovement * yMovement);

		(len != 0) ? xMovement /= len : 0;
		(len != 0) ? yMovement /= len : 0;

		tempX = xMovement * speed;
		tempY = yMovement * speed;

		moveDir(sf::Vector2f(tempX, tempY));

		//tempX = xMovement * speed;
		//tempY = yMovement * speed;

		//moveDir(sf::Vector2f(tempX*((tempX != 0 && tempY != 0) ? 0.707 : 1), tempY));
	}
	if (dest == getPos())
	{
		isMoving = false;
		tempX = 0;
		tempY = 0;
		moveDir(sf::Vector2f(0, 0));
		return true; //Return true when destination is reached
	}

	

	return false; //Return false when destination is not reached
}
int Obj::moveToQueue()
{
	if (vec_moveToQueue.size() > 0)
	{
		if (moveTo(vec_moveToQueue[0]))
		{
			vec_moveToQueue.erase(vec_moveToQueue.begin());
			curMoveToQueue++;
			return curMoveToQueue;
		}
	}
	else
	{
		curMoveToQueue = 0;
		return -1;
	}
}

//Graphics and animations

void Obj::setScale(float x, float y)
{
	scaleX = x;
	scaleY = y;
}

void Obj::setMyTexture(std::string ImgDir, sf::IntRect rect = sf::IntRect(0,0,0,0))
{
	if (!isAnimated)
	{
		if (!texture.loadFromFile(ImgDir))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			texture.loadFromFile(".\\textures\\missing_error.png");
		}
	}
	if(isAnimated)
	{
		if (!texture.loadFromFile(ImgDir, rect))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			texture.loadFromFile(".\\textures\\missing_error.png");
		}
	}
	obj.setTexture(&texture);
	obj.setScale(scaleX, scaleY);
}

void Obj::setupStatic(std::string ImgDirI)
{
	if (!isInitialized)
	{
		isAnimated = false();
		ImgDir = ImgDirI;
		setMyTexture(ImgDir);
	}
	else
	{
		std::cerr << "Object [" << this << "] is already initialized\n";
	}
}

//***[Note] If you want to make animated object **Do not set texture before using this function or it will result in werid animation [Note]***
void Obj::setupAnim(std::string ImgDirI, int frameIWidth, int frameIHeight, int frameIRows = 1, int frameIColumns = 1)
{
	if (!isInitialized)
	{
		isAnimated = true;

		frameWidth = frameIWidth;
		frameHeight = frameIHeight;
		frameRows = frameIRows;
		frameColumns = frameIColumns;

		ImgDir = ImgDirI;

		setMyTexture(ImgDir, sf::IntRect(0, 0, frameWidth, frameHeight));
	}
	else
	{
		std::cerr << "Object [" << this << "] is already initialized\n";
	}
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
		setMyTexture(ImgDir, rect);

		return curFrame;
	}
	else
	{
		std::cerr << "Object [" << this << "] is already initialized\n";
		return -69;
	}
}