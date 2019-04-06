#pragma once

#include "object.h"

class Player : public Obj
{
public:
	Player(std::string, std::vector<Obj*> *);
	void control(bool, bool, bool, bool);


protected:
	sf::Texture t;

	std::string name = "A";

	float speed = 5.0f;
};

Player::Player(std::string ImgDir, std::vector<Obj*> *ObjListInput) //Problem with vector list
{
	pushToVector(ObjListInput);
	setTexture(ImgDir);
}

void Player::control(bool Right, bool Left, bool Down, bool Up)
{
	float xMovement = float(Right - Left);
	float yMovement = float(Down - Up);

	obj.move(sf::Vector2f(xMovement*speed, yMovement*speed));
}