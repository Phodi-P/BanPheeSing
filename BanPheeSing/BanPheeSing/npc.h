#pragma once

#include "object.h"

class Npc : public Obj
{
public:
	Npc();
	Npc(sf::Vector2f, std::string, int, int, int, int, std::string);
	int walkingAnimate(int);
private:

	std::string name;
};
Npc::Npc()
{
	//Default
}
Npc::Npc(sf::Vector2f pos, std::string ImgIDir, int frameW, int frameH, int frameRow , int frameCol, std::string n = "NPC")
{
	name = n;
	setPos(pos);
	ImgDir = ImgIDir;
	obj.setSize(sf::Vector2f(frameW, frameH));
	obj.setOrigin(sf::Vector2f(frameW / 2, frameH / 2));
	setupAnim(ImgIDir, frameW, frameH, frameRow, frameCol);
}

int Npc::walkingAnimate(int fps = 6)
{
	int DirX = 0;
	int DirY = 0;

	DirX = CUt::sign(xSpeed);
	DirY = CUt::sign(ySpeed);


	if (DirX == 0 && DirY == 0)
	{
		animate(1); //Idle
	}
	if (DirX == 1 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
	{
		animationClock.restart();
		if (curFrame < 6 || curFrame > 8) animate(6);
		if (animate(-1, 0) > 8) animate(6);

	}
	if (DirX == -1 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
	{
		animationClock.restart();
		if (curFrame < 3 || curFrame > 5) animate(3);
		if (animate(-1, 0) > 5) animate(3);
	}
	if (DirY == 1 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
	{
		animationClock.restart();
		if (curFrame < 0 || curFrame > 2) animate(0);
		if (animate(-1, 0) > 2) animate(0);

	}
	if (DirY == -1 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
	{
		animationClock.restart();
		if (curFrame < 9 || curFrame >= 11) animate(9);
		if (animate(-1, 0) >= 11) animate(9);
	}
	return curFrame;
}