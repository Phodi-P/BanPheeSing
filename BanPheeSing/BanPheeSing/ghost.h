#pragma once

#include "npc.h"

class Ghost :public Npc
{
public:
	Ghost(sf::Vector2f, std::string, int, int, int, int);
	int chase(sf::Vector2f, sf::Vector2f, sf::Vector2f);

private:
	enum state
	{
		spawn = 0,
		startComingOut = 1,
		walking = 2,
		running = 3,
		screaming = 4,
		lost = 5,
		kill = 6
	};
	state curState;
	sf::Clock runClock;
	float runTimeMax = 2.5f;

};

Ghost::Ghost(sf::Vector2f pos, std::string ImgIDir, int frameW, int frameH, int frameRow, int frameCol)
{
	setPos(pos);
	ImgDir = ImgIDir;
	obj.setSize(sf::Vector2f(frameW, frameH));
	obj.setOrigin(sf::Vector2f(frameW / 2, frameH / 2));
	setupAnim(ImgIDir, frameW, frameH, frameRow, frameCol);

	curState = spawn;
}

//Start chasing targetPos
//returns 0 while chasing
//returns 1 when target get away
//reuturns 2 when target is caught
int Ghost::chase(sf::Vector2f startPos, sf::Vector2f startDir, sf::Vector2f targetPos)
{
	float distX = targetPos.x - getPos().x;
	float distY = targetPos.y - getPos().y;
	float dist = std::sqrtf(distX*distX + distY * distY);
	switch(curState)
	{
	case spawn:
		setPos(startPos);
		curState = startComingOut;
		break;
	case startComingOut:
		if (moveTo(startPos + startDir)) curState = walking;
		break;
	case walking:
		setSpd(1.8f);
		moveTo(targetPos);
		if (dist > 500) curState = running;
		break;
	case running:
		setSpd(6.0f);
		moveTo(targetPos);
		if (runClock.getElapsedTime().asSeconds() >= runTimeMax)
		{
			curState = walking;
			runClock.restart();
		}
		break;
	}
	walkingAnimate();
	return 0;
}