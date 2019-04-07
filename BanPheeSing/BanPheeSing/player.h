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


protected:

	std::string name = "A";

	//Sprite sheet animation details
	/*
	sf::Texture t;
	std::string ImgDir;
	sf::Clock animationClock;
	int frameWidth = 32;
	int frameHeight = 32;
	int frameRows = 1;
	int frameColumns = 1;
	int curFrame = 0;
	*/

	float speed = 1.5f;
	float sprintSpeed = 4.0f;
};

Player::Player(std::string ImgDirI, int frameIWidth, int frameIHeight, int frameIRows = 1, int frameIColumns = 1) //Problem with vector list
{
	isAnimated = true;

	frameWidth = frameIWidth;
	frameHeight = frameIHeight;
	frameRows = frameIRows;
	frameColumns = frameIColumns;

	ImgDir = ImgDirI;

	setTexture(ImgDir, sf::IntRect(0,0,frameWidth,frameHeight));
}

/*
//***[Note] This function will advance the animation forward if the input is -1(Default) and set to specific frame when input is not -1 [Note]***
int Player::animate(int setFrame = -1, int fps = 1)
{
	sf::IntRect rect;
	if (setFrame != -1)
	{
		curFrame = setFrame;
	}
	else if(setFrame == -1)
	{
		if (fps > 0 && animationClock.getElapsedTime().asSeconds() > 1.0f / fps)
		{
			animationClock.restart();
			curFrame++;
		}
		curFrame++;
		if (curFrame > (frameColumns*frameRows) - 1) curFrame = 0;
	}
	int tarRow = std::ceil(curFrame / frameColumns);
	int tarCol = (curFrame % frameColumns);

	rect = sf::IntRect(frameWidth*tarCol, frameHeight*tarRow, (frameWidth*tarCol) + frameWidth, (frameHeight*tarRow) + frameHeight);

	setTexture(ImgDir, rect);

	return curFrame;
}
*/
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
	if (Sprint) spd = sprintSpeed;
	else spd = speed;

	if(xMovement != 0 && yMovement != 0) obj.move(sf::Vector2f(xMovement*spd*0.707, yMovement*spd*0.707)); //Fix diagnal movement speed issue
	else obj.move(sf::Vector2f(xMovement*spd, yMovement*spd));

	
}