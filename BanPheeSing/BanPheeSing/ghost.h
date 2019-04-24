#pragma once

#include "npc.h"

class Ghost :public Npc
{
public:
	Ghost(sf::Vector2f, std::string, int, int, int, int);
	int chase(sf::Vector2f, sf::Vector2f, Player);

	//void drawDist(sf::RenderWindow &);

	bool canWalk = true;
	bool canCollide = true;
	sf::Vector2f nonZeroSpd;

private:
	enum state
	{
		spawn = 0,
		startComingOut = 1,
		walking = 2,
		running = 3,
		screaming = 4,
		lost = 5,
		kill = 6, 
		slow = 7
	};
	state curState;
	sf::Clock runClock;
	float runTime = 3.5f;
	float slowTime = 5.0f;
	float timeBeforeRun = 12.0f;
	float killDist = 50.0f;

	//QuickText showDist;

};

Ghost::Ghost(sf::Vector2f pos, std::string ImgIDir, int frameW, int frameH, int frameRow, int frameCol)
{
	setPos(pos);
	ImgDir = ImgIDir;
	obj.setSize(sf::Vector2f(frameW, frameH));
	obj.setOrigin(sf::Vector2f(frameW / 2, frameH / 2));
	setupAnim(ImgIDir, frameW, frameH, frameRow, frameCol);

	setVisibility(false);
	curState = spawn;

	//showDist.setColor(sf::Color::Red);
	//showDist.setSize(42);
}

//Start chasing targetPos
//returns 0 while chasing
//returns 1 when target get away
//reuturns 2 when target is caught
int Ghost::chase(sf::Vector2f startPos, sf::Vector2f startDir, Player target)
{
	float distX = target.getPos().x - getPos().x;
	float distY = target.getPos().y - getPos().y;
	float dist = std::sqrtf(distX*distX + distY * distY);
	//showDist.setPos(getPos());
	//showDist.setString(std::to_string(dist));
	switch(curState)
	{
	case spawn:
		canCollide = false;
		setVisibility(true);
		setPos(startPos);
		curState = startComingOut;
		break;
	case startComingOut:
		canCollide = false;
		setSpd(1.0f);
		if (moveTo(startPos + startDir)) curState = walking;
		runClock.restart();
		break;
	case walking:
		canCollide = true;
		setSpd(7.8f + (1.0f - (dist / 1500.0f))*5.0f);
		if(canWalk) moveTo(target.getPos());
		if (runClock.getElapsedTime().asSeconds() >= timeBeforeRun)
		{
			runClock.restart();
			curState = running;
		}
		if (dist > 1200 || dist < 500) curState = running;
		if (dist < killDist)
		{
			if (Collision::BoundingBoxTestRect(getObj(), target.getObj())) curState = kill;
		}
		if (dist > 1500) curState = lost;
		break;
	case running:
		canCollide = true;
		setSpd(11.0f+(1.0f-(dist/1500.0f))*8.0f);
		if (canWalk) moveTo(target.getPos());
		if (runClock.getElapsedTime().asSeconds() >= runTime)
		{
			curState = slow;
			runClock.restart();
		}
		if (dist < killDist)
		{
			if (Collision::BoundingBoxTestRect(getObj(), target.getObj())) curState = kill;
		}
		break;
	case slow:
		canCollide = true;
		setSpd(2.5f);
		if (canWalk) moveTo(target.getPos());
		if (runClock.getElapsedTime().asSeconds() >= slowTime)
		{
			curState = walking;
			runClock.restart();
		}
		if (dist < killDist)
		{
			if (Collision::BoundingBoxTestRect(getObj(), target.getObj())) curState = kill;
		}
		break;
	case kill:
		canCollide = false;
		std::cout << "Killed at dist = " << dist << "\n";
		setVisibility(false);
		curState = spawn;
		return 2;
		break;
	case lost:
		canCollide = false;
		std::cout << "Lost at dist = " << dist << "\n";
		setVisibility(false);
		curState = spawn;
		return 1;
		break;
	}
	walkingAnimate();
	if (getSpd().x != 0 || getSpd().y != 0) nonZeroSpd = getSpd();
	return 0;
}
/*
void Ghost::drawDist(sf::RenderWindow &window)
{
	showDist.draw(window);
}*/