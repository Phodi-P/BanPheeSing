#pragma once

#include "npc.h"

class Ghost :public Npc
{
public:
	Ghost(sf::Vector2f, std::string, int, int, int, int);
	int chase(sf::Vector2f, sf::Vector2f, sf::Vector2f);

	void drawDist(sf::RenderWindow &);

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
	float runTime = 2.5f;
	float slowTime = 6.0f;
	float timeBeforeRun = 12.0f;
	float killDist = 5.0f;

	QuickText showDist;

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

	showDist.setColor(sf::Color::Red);
	showDist.setSize(42);
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
	showDist.setPos(getPos());
	showDist.setString(std::to_string(dist));
	switch(curState)
	{
	case spawn:
		setVisibility(true);
		setPos(startPos);
		curState = startComingOut;
		break;
	case startComingOut:
		setSpd(1.0f);
		if (moveTo(startPos + startDir)) curState = walking;
		runClock.restart();
		break;
	case walking:
		setSpd(1.7f);
		moveTo(targetPos);
		if (runClock.getElapsedTime().asSeconds() >= timeBeforeRun)
		{
			runClock.restart();
			curState = running;
		}
		if (dist > 1200 || dist < 500) curState = running;
		if (dist <= killDist) curState = kill;
		if (dist > 1500) curState = lost;
		break;
	case running:
		setSpd(5.9f);
		moveTo(targetPos);
		if (runClock.getElapsedTime().asSeconds() >= runTime)
		{
			curState = slow;
			runClock.restart();
		}
		if (dist <= killDist) curState = kill;
		break;
	case slow:
		setSpd(0.8f);
		moveTo(targetPos);
		if (runClock.getElapsedTime().asSeconds() >= slowTime)
		{
			curState = walking;
			runClock.restart();
		}
		if (dist <= killDist) curState = kill;
	case kill:
		std::cout << "Killed at dist = " << dist << "\n";
		setVisibility(false);
		curState = spawn;
		return 2;
	case lost:
		std::cout << "Lost at dist = " << dist << "\n";
		setVisibility(false);
		curState = spawn;
		return 1;
	}
	walkingAnimate();
	return 0;
}

void Ghost::drawDist(sf::RenderWindow &window)
{
	showDist.draw(window);
}