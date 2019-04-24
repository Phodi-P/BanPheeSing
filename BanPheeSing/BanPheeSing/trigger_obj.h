#pragma once
#include "custom_utility.h"
#include "player.h"
#include "npc.h"
#include "ghost.h"

class triggerObj
{
public:
	triggerObj(Event*, std::string, std::string, sf::Vector2f, sf::Vector2f, float);
	bool collide(Player &);
	bool collide(Npc &);
	bool collide(Ghost &);
	sf::RectangleShape obj;

	bool moveAble;
	bool triggered = false;
	Event *evnt;
	std::string id,type;
private:

};

triggerObj::triggerObj(Event *evnt, std::string id, std::string type, sf::Vector2f pos, sf::Vector2f size, float scale = 4.0f)
{
	this->id = id;
	this->type = type;
	this->evnt = evnt;
	obj.setPosition({ pos.x*scale,pos.y*scale });
	obj.setSize({ size.x*scale,size.y*scale });
	this->moveAble = moveAble;
}

bool triggerObj::collide(Player &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		//std::cout << "event: " << id << " is being triggered\n";
		if (type == "Once")
		{
			if (!triggered)
			{
				triggered = true;
				evnt->triggerEvent(id);
			}
		}
		else
		{
			triggered = true;
			evnt->triggerEvent(id);
		}
		return true;
	}
	else
	{
		if (type == "Once")
		{

		}
		else
		{
			triggered = false;
		}
		return false;
	}
}

bool triggerObj::collide(Npc &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()))
	{
		evnt->triggerEvent(id);
		return true;
	}
	else
	{
		return false;
	}
}

bool triggerObj::collide(Ghost &target)
{
	if (Collision::BoundingBoxTestRect(obj, target.getObj()) && target.canCollide)
	{
		evnt->triggerEvent(id);
		return true;
	}
	else
	{
		return false;
	}
}