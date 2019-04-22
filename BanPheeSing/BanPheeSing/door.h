#include "custom_utility.h"
class Door {
public:
	bool open=false;
	sf::RectangleShape sq;
	sf::RectangleShape sq2;
	sf::Texture hole;
	sf::Texture door;
	void draw(sf::RenderWindow&);
	int x;
	int y;
	Door(int,int);
	void setDoor(bool);
};
Door::Door(int x,int y) {
	hole.loadFromFile(".\\textures\\test.jpg");
	door.loadFromFile(".\\textures\\missing_error.png");
	sq.setSize(sf::Vector2f(100, 40));
	sq2.setSize(sf::Vector2f(60, 50));
	sq.setTexture(&hole);
	sq2.setTexture(&door);
	sq.setPosition(x,y);
	sq2.setPosition(x,y);
	
}
void Door::draw(sf::RenderWindow &x) {
	x.draw(sq);
	if (open==false) {
		x.draw(sq2);
	}
}
void Door::setDoor(bool check) {
	open = check;
}