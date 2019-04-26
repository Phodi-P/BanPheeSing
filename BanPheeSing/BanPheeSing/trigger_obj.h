#pragma once
#include "custom_utility.h"
#include "player.h"
#include "npc.h"
#include "ghost.h"

class triggerObj
{
public:
	triggerObj(Event*, std::string, std::string, sf::Vector2f, sf::Vector2f, float);
	triggerObj(Event*, std::string, std::string, sf::Vector2f, float);

	bool collide(Player &);
	bool collide(Npc &);
	bool collide(Ghost &);
	void update(Player&);
	void draw(sf::RenderWindow &);

	Event *evnt;
	sf::RectangleShape obj;
	sf::Sprite sprite;
	sf::Texture texture, overlay;

	bool moveAble;
	bool canActive;
	bool canDraw;
	bool triggered = false;
	
	std::string id;



	//Types of event
	// once -> only activate once , can be manually reactivate with .triggered = false;
	// semi-once -> activate once , can be activate again when not collided
	// continuous -> activate continuously when collided
	std::string type;



	//Types of item
	//lamp -> use to expell ghost temporally
	std::string item_type;
private:

};

//For area trigger
triggerObj::triggerObj(Event *evnt, std::string id, std::string type, sf::Vector2f pos, sf::Vector2f size, float scale = 4.0f)
{
	this->id = id;
	this->type = type;
	this->evnt = evnt;
	obj.setPosition({ pos.x*scale,pos.y*scale });
	obj.setSize({ size.x*scale,size.y*scale });
	this->moveAble = moveAble;

	canActive = false;
}

//For item
triggerObj::triggerObj(Event *evnt, std::string id, std::string item_type, sf::Vector2f pos, float scale = 1.0f)
{
	this->id = id;
	this->item_type = item_type;
	this->evnt = evnt;


	this->canActive = true;
	if (item_type == "lamp")
	{
		std::cout << "Lamp created\n";
		obj.setPosition({ pos.x*scale,pos.y*scale });
		obj.setSize({ 1 * scale,1 * scale });

		sprite.setPosition({ pos.x*scale,pos.y*scale });
		this->moveAble = false;
		canDraw = true;
		type = "semi-once";
		
		texture.loadFromFile(".//textures//door_vertical.png"); //Place holder
		overlay.loadFromFile(".//textures//light.png");

		obj.setTexture(&texture);
		sprite.setTexture(overlay);

		triggered = true;
	}
}

bool triggerObj::collide(Player &target)
{
	if (!canActive)
	{
		if (Collision::BoundingBoxTestRect(obj, target.getObj()))
		{
			std::cout << "event: " << id << " is being triggered\n";
			if (type == "once" || type == "semi-once")
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
			if (type == "once")
			{

			}
			else
			{
				triggered = false;
			}
			return false;
		}
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

void triggerObj::update(Player &Player)
{
	collide(Player);
	float dist = CUt::dist(Player.getPos(), obj.getPosition());
	if (dist < 30 && sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if (type == "once" || type == "semi-once")
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
	}
	else
	{
		if (type == "once")
		{

		}
		else
		{
			triggered = false;
		}
	}
}

void triggerObj::draw(sf::RenderWindow &window)
{
	if (canDraw)
	{
		if (item_type == "lamp")
		{
			std::cout << "Lamp drawing\n";
			window.draw(obj);
			if(triggered) window.draw(sprite);
		}
	}
}