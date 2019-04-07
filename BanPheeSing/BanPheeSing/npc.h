#pragma once

#include "object.h"

class Npc : public Obj
{
public:
	Npc(sf::Vector2f, std::string, std::string);
private:

	std::string name;
	float speed = 5.0f;
};

Npc::Npc(sf::Vector2f pos, std::string ImgDir, std::string n = "NPC")
{
	name = n;
	setTexture(ImgDir);
	setPos(pos);
}