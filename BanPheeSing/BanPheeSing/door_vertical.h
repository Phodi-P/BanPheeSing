#include "custom_utility.h"
#include "event.h"
#include "Collision.hpp"
#include "player.h"
#include "npc.h"
class DoorVertical {
public:
	bool lock = false;
	bool open = false;
	bool left;
	sf::RectangleShape sq;
	sf::RectangleShape collisionMask;

	sf::Vector2f pos;
	float scale;
	std::string DoorVertical_id;

	DoorVertical(sf::Vector2f, std::string, bool, float);
	void update(Event &, Player &);
	bool collide(Player &);
	void setDoorVertical(bool);
	void draw(sf::RenderWindow&);

private:
	sf::Texture door;
};
DoorVertical::DoorVertical(sf::Vector2f pos, std::string DoorVertical_id, bool left, float scale = 4.0f) {
	sq.setPosition(pos);
	sq.setSize(sf::Vector2f(16 * 1 * scale, 16 * 2 * scale));

	collisionMask.setPosition(pos);
	collisionMask.setSize(sf::Vector2f(16 * 1 * scale, 16 * 2 * scale));

	if(left) door.loadFromFile(".\\textures\\door_vertical_left.png");
	else door.loadFromFile(".\\textures\\door_vertical_right.png");
	sq.setTexture(&door);

	this->DoorVertical_id = DoorVertical_id;

}
bool DoorVertical::collide(Player &target)
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
void DoorVertical::update(Event &event, Player &Player)
{
	std::cout << DoorVertical_id << "\n";
	if (event.checkEvent(DoorVertical_id + "+lock"))
	{
		lock = true;
		std::cout << "Locked\n";
	}
	if (event.checkEvent(DoorVertical_id + "+unlock"))
	{
		lock = false;
		std::cout << "Unlocked\n";
	}
	if (event.checkEvent(DoorVertical_id + "+open"))
	{
		if (!lock)
		{
			open = true;
			std::cout << "Open\n";
		}
	}
	if (event.checkEvent(DoorVertical_id + "+close"))
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
void DoorVertical::draw(sf::RenderWindow &x) {
	if (!open) x.draw(sq);
}
void DoorVertical::setDoorVertical(bool check) {
	open = check;
}