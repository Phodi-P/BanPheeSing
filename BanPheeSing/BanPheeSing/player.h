#pragma once

#include "object.h"
#include <cmath>

class Player : public Obj
{
public:
	Player(std::string, int, int, int, int);
	void control(bool, bool, bool, bool, bool);

	int walkingAnimate(int, int, int);
	int getCurrentFrame();

	bool isSprinting = false;


protected:

	std::string name = "A";


	//Game Mechanics

	float speed = 1.5f;
	float sprintSpeed = 4.0f;

	sf::Clock staminaClock;

	bool canSprint = true; 

	float maxStamina = 100.0f; //[Editable]
	float minStamina = 50.0f; //[Editable]
	float curStamina = maxStamina;

	float staminaRegenRate = 7.5f; //[Editable] //How much stamina will Regen/Drain in 1 second
	float staminaDrainRate = 30.5f; //[Editable]

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
}

//***[Note] This function is hard coded for 3x4 sprite sheet DirX is either 1,0,-1 DirY is either 1,0,-1***
int Player::walkingAnimate(int DirX = 0, int DirY = 0, int fps = 4)
{
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

int Player::getCurrentFrame()
{
	return curFrame;
}

void Player::control(bool Right, bool Left, bool Down, bool Up, bool Sprint)
{
	float xMovement = float(Right - Left);
	float yMovement = float(Down - Up);

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
			if(xMovement != 0 || yMovement != 0) curStamina--;
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

	if(xMovement != 0 && yMovement != 0) moveDir(sf::Vector2f(xMovement*spd*0.707, yMovement*spd*0.707)); //Fix diagnal movement speed issue
	else moveDir(sf::Vector2f(xMovement*spd, yMovement*spd));

	
}