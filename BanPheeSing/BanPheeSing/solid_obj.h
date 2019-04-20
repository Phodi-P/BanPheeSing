#pragma once
#include "player.h"

class solidObj
{
public:
	solidObj(sf::Vector2f, sf::Vector2f, bool);
	bool collide(Player &);
	bool collide(Ghost &);
	sf::RectangleShape obj;

	bool moveAble;
private:

};

solidObj::solidObj(sf::Vector2f pos, sf::Vector2f size, bool moveAble = false)
{
	obj.setPosition(pos);
	obj.setSize(size);
	this->moveAble = moveAble;
}

bool solidObj::collide(Player &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		target.canWalk = false;
		target.moveDir(sf::Vector2f(-target.nonZeroSpd.x*10000*deltaTime,-target.nonZeroSpd.y*10000*deltaTime));
		if (moveAble) obj.move(sf::Vector2f(target.nonZeroSpd.x * 10000 * deltaTime, target.nonZeroSpd.y * 10000 * deltaTime));
		return true;
	}
	else
	{
		target.canWalk = true;
		return false;
	}
}

bool solidObj::collide(Ghost &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		//target.canWalk = false;
		target.moveDir(sf::Vector2f(-target.nonZeroSpd.x * 100000 * deltaTime, -target.nonZeroSpd.y * 100000 * deltaTime));
		return true;
	}
	else
	{
		target.canWalk = true;
		return false;
	}
}

