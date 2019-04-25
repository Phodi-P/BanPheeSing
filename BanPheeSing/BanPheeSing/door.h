#include "custom_utility.h"
#include "event.h"
#include "Collision.hpp"
#include "player.h"
#include "npc.h"
class Door {
public:
	bool lock = false;
	bool open = false;
	sf::RectangleShape sq;
	sf::RectangleShape collisionMask;

	bool vertical;

	sf::Vector2f pos;
	float scale;
	std::string door_id;

	Door(sf::Vector2f, sf::Vector2f, std::string, float);
	void update(Event & , Player &);
	bool collide(Player &);
	void setDoor(bool);
	void draw(sf::RenderWindow&);

private:
	sf::Texture door;
};
Door::Door(sf::Vector2f pos, sf::Vector2f size, std::string door_id, float scale = 4.0f)
{
	vertical = (size.y > size.x);

	sq.setPosition(pos);
	collisionMask.setPosition(pos);
	
	if (vertical)
	{
		door.loadFromFile(".\\textures\\door_vertical.png");
		sq.setSize(sf::Vector2f(16 * 4 * scale, 16 * 4 * scale));
		collisionMask.setSize(sf::Vector2f(16 * 1 * scale, 16 * 2 * scale));
	}
	else
	{
		door.loadFromFile(".\\textures\\door.png");

		sq.setSize(sf::Vector2f(16 * 4 * scale, 16 * 4 * scale));
		collisionMask.setSize(sf::Vector2f(16 * 4 * scale, 16 * 3 * scale));
	}
	sq.setTexture(&door);

	this->door_id = door_id;
	
}
bool Door::collide(Player &target)
{
	if (Collision::BoundingBoxTestRect(collisionMask, target.getObj()))
	{
		target.canWalk = false;
		target.moveDir(sf::Vector2f(-target.nonZeroSpd.x*1.05*deltaTime, -target.nonZeroSpd.y*1.05*deltaTime));
		return true;
	}
	else
	{
		target.canWalk = true;
		return false;
	}
}
void Door::update(Event &event, Player &Player)
{
	std::cout << door_id << "\n";
	if (event.checkEvent(door_id + "+lock"))
	{
		lock = true;
		std::cout << "Locked\n";
	}
	if (event.checkEvent(door_id + "+unlock"))
	{
		lock = false;
		std::cout << "Unlocked\n";
	}
	if (event.checkEvent(door_id + "+open"))
	{
		if (!lock)
		{
			open = true;
			std::cout << "Open\n";
		}
	}
	if (event.checkEvent(door_id + "+close"))
	{
		open = false;
		std::cout << "Open\n";
	}

	if (lock && open) open = false;

	if (!open)
	{
		collide(Player);
	}

}
void Door::draw(sf::RenderWindow &x) {
	if (!open) x.draw(sq);
}
void Door::setDoor(bool check) {
	open = check;
}