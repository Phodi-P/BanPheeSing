#pragma once
#include"custom_utility.h"
#include"button.h"

#define MAX_NUMBER_OF_ITEMS 2

class StartMenu {
	public:
		StartMenu(float,float,std::string,sf::Font &);

		void draw(sf::RenderWindow &);
		void moveUp();
		void moveDown();
	private:
		int selectedItemIndex;
		sf::Sprite background;
		sf::Texture backgroundTexture;
		std::vector<Button> menu;
};

StartMenu::StartMenu(float windowWidth, float windowHeight,std::string backgroundPath,sf::Font &font) {
	selectedItemIndex = 0;

	float posX = windowWidth / 2;
	float posY = ((windowHeight/2) / (MAX_NUMBER_OF_ITEMS + 1));
	menu.push_back(Button("Play", "1", sf::Vector2f(posX, (windowHeight / 2) + posY * 1), font));
	menu.push_back(Button("Exit", "2", sf::Vector2f(posX, (windowHeight / 2) + posY * 2), font));
	menu[selectedItemIndex].select();
	backgroundTexture.loadFromFile(backgroundPath);
}

void StartMenu::draw(sf::RenderWindow &window) {
	background.setTexture(backgroundTexture);
	window.draw(background);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
		menu[i].drawButton(window);
	}
}

void StartMenu::moveUp() {
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].unselect();
		selectedItemIndex--;
		menu[selectedItemIndex].select();
	}
}

void StartMenu::moveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].unselect();
		selectedItemIndex++;
		menu[selectedItemIndex].select();
	}
}