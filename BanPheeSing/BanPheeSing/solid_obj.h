#pragma once
#include "player.h"

class solidObj
{
public:
	solidObj(sf::Vector2f, sf::Vector2f, float, bool);
	bool collide(Player &);
	bool collide(Npc &);
	bool collide(Ghost &);
	sf::RectangleShape obj;

	bool moveAble;
private:

};

solidObj::solidObj(sf::Vector2f pos, sf::Vector2f size, float scale = 4.0f, bool moveAble = false)
{
	obj.setPosition({ pos.x*scale,pos.y*scale });
	obj.setSize({ size.x*scale,size.y*scale });
	this->moveAble = moveAble;
}

bool solidObj::collide(Player &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		target.canWalk = false;
		target.moveDir(sf::Vector2f(-target.nonZeroSpd.x*1.05*deltaTime,-target.nonZeroSpd.y*1.05*deltaTime));
		if (moveAble) obj.move(sf::Vector2f(target.nonZeroSpd.x * 1.05 * deltaTime, target.nonZeroSpd.y * 1.05 * deltaTime));
		return true;
	}
	else
	{
		target.canWalk = true;
		return false;
	}
}

bool solidObj::collide(Npc &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		//target.getSpd
		target.moveDir(sf::Vector2f(-target.getSpd().x*1.05*deltaTime, -target.getSpd().y*1.05*deltaTime));
		if (moveAble) obj.move(sf::Vector2f(target.getSpd().x * 1.05 * deltaTime, target.getSpd().y * 1.05 * deltaTime));
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
	if (Collision::BoundingBoxTestRect(obj, target.getObj()) && target.canCollide)
	{
		//target.canWalk = false;
		target.moveDir(sf::Vector2f(-target.nonZeroSpd.x * 1.05 * deltaTime, -target.nonZeroSpd.y * 1.05 * deltaTime));
		return true;
	}
	else
	{
		target.canWalk = true;
		return false;
	}
}

