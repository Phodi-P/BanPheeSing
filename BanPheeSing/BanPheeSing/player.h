#pragma once

#include "object.h"


class Player : public Obj
{
public:
	Player(std::string, int, int, int, int);
	void control(bool, bool, bool, bool, bool);

	int walkingAnimate(int, int, int);
	int walkingAnimateAuto(int);
	int getCurrentFrame();
	void drawStamina(sf::RenderWindow &);

	bool isAuto = false;
	bool isSprinting = false;
	bool canWalk = true;

	//std::vector<sf::Vector2f> trailPos;
	//int trailCount = 0;
	//float trailTime = 0;
	//float trailTimeDist = 40;

	sf::Vector2f nonZeroSpd;


protected:

	std::string name = "A";
	sf::RectangleShape staminaBar;

	//Game Mechanics

	float speed = 5.0f;
	float sprintSpeed = 12.0f;

	sf::Clock staminaClock;

	bool canSprint = true; 

	float maxStamina = 100.0f; //[Editable]
	float minStamina = 50.0f; //[Editable]
	float curStamina = maxStamina;

	float staminaRegenRate = 7.5f; //[Editable] //How much stamina will Regen/Drain in 1 second
	float staminaDrainRate = 30.5f; //[Editable]

	float staminaBarMaxWidth = 100.0f;

};

Player::Player(std::string ImgDirI, int frameIWidth, int frameIHeight, int frameIRows = 1, int frameIColumns = 1) //Problem with vector list
{
	isAnimated = true;

	frameWidth = frameIWidth;
	frameHeight = frameIHeight;
	frameRows = frameIRows;
	frameColumns = frameIColumns;

	ImgDir = ImgDirI;

	setMyTexture(ImgDir, sf::IntRect(0,0,frameWidth,frameHeight));

	staminaBar.setFillColor(sf::Color::Green);

	setSpd(this->speed);

	//trailPos.push_back({ 0,0 });
	//trailPos.push_back({ 0,0 });
	//trailPos.push_back({ 0,0 });
}

//***[Note] This function is hard coded for 3x4 sprite sheet DirX is either 1,0,-1 DirY is either 1,0,-1***
int Player::walkingAnimate(int DirX = 0, int DirY = 0, int fps = 4)
{
	if (isAuto == false)
	{
		//std::cout << "Running\n";
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
	return 0;
}

int Player::walkingAnimateAuto(int fps = 6)
{
	if (isAuto == true)
	{
		int DirX = 0;
		int DirY = 0;

		DirX = CUt::sign(getSpd().x);
		DirY = CUt::sign(getSpd().y);

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
}

int Player::getCurrentFrame()
{
	return curFrame;
}

void Player::control(bool Right, bool Left, bool Down, bool Up, bool Sprint)
{
	if (canWalk)
	{
		float xMovement = float(Right - Left);
		float yMovement = float(Down - Up);
		/*
		if (xMovement != 0 || yMovement != 0)
		{
			trailTime += deltaTime;
			if (trailTime > trailTimeDist)
			{
				trailTime = 0;
				trailPos[trailCount] = getPos();
				trailCount++;
				if (trailCount > 2) trailCount = 0;
			}
		}*/

		float spd;
		if (!canSprint && curStamina >= minStamina)
		{
			canSprint = true;
		}
		if (Sprint && canSprint)
		{
			spd = sprintSpeed;
			if (staminaClock.getElapsedTime().asSeconds() > 1.0f / staminaDrainRate)
			{
				staminaClock.restart();
				isSprinting = true;
				if (xMovement != 0 || yMovement != 0) curStamina--;
				if (curStamina <= 0)
				{
					curStamina = 0;
					canSprint = false;
				}
			}
		}
		else
		{
			isSprinting = false;
			spd = speed;
			if (staminaClock.getElapsedTime().asSeconds() > 1.0f / staminaRegenRate)
			{
				staminaClock.restart();
				curStamina++;
				if (curStamina > maxStamina) curStamina = maxStamina;
			}
		}


		float len = std::sqrt(xMovement*xMovement + yMovement * yMovement);

		(len != 0) ? xMovement /= len : 0;
		(len != 0) ? yMovement /= len : 0;

		moveDir(sf::Vector2f(xMovement * spd * deltaTime, yMovement * spd * deltaTime));

		if (getSpd().x != 0 || getSpd().y != 0) nonZeroSpd = getSpd();

		float staminaBarCurWidth = staminaBarMaxWidth * (curStamina / maxStamina);
		if (curStamina < maxStamina) staminaBar.setSize(sf::Vector2f(staminaBarCurWidth, 10.0f));
		else staminaBar.setSize(sf::Vector2f(0, 0));
		staminaBar.setPosition(getPos() + sf::Vector2f(-(staminaBarCurWidth / 2), -80.0f));

		//moveDir(sf::Vector2f(xMovement*spd*deltaTime, yMovement*spd*deltaTime));

		//if(xMovement != 0 && yMovement != 0) moveDir(sf::Vector2f(xMovement*spd*0.707*deltaTime, yMovement*spd*0.707*deltaTime)); //Fix diagnal movement speed issue
		//else moveDir(sf::Vector2f(xMovement*spd*deltaTime, yMovement*spd*deltaTime));

	}
	
}

void Player::drawStamina(sf::RenderWindow &window)
{
	window.draw(staminaBar);
}