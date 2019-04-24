#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#include "event.h"

//Global setting variables
const int WindowWidth = 1920;
const int WindowHeight = 1080;
const int RoomWidth = 1920;
const int RoomHeight = 1080;

float deltaTime = 0.0f;

bool gamePause = false;

Event testEvent;

namespace CUt //CUt is short for Custom Utility
{
	//***[Note] This function returns sign of value (-1,0,1) [Note]***
	template <typename T>
	T sign(T input)
	{
		return (T(0) < input) - (input < T(0));
	}

	//***[Note] This function returns distance between two position [Note]***
	float dist(sf::Vector2f pos1, sf::Vector2f pos2)
	{
		return sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y));
	}
}

sf::Vector2f getViewOffset(sf::View &view)
{
	return view.getCenter() - sf::Vector2f(WindowWidth / 2, WindowHeight / 2);
}
 

/*
class QuickText {
public:
	QuickText();
	QuickText(sf::Vector2f, std::string, sf::Color, int);
	void setPos(sf::Vector2f);
	void setString(std::string);
	void setSize(int);
	void setColor(sf::Color);
	void draw(sf::RenderWindow &);
private:
	sf::Text text;
	sf::Font font;
};

QuickText::QuickText(sf::Vector2f pos, std::string string, sf::Color color = sf::Color::White, int size = 16)
{
	font.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf");
	text.setFont(font);
	text.setFillColor(color);
	text.setCharacterSize(size);
	text.setString(string);
	text.setPosition(pos);
}

QuickText::QuickText()
{
	font.loadFromFile(".\\fonts\\PrintAble4U Regular.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(16);
	text.setPosition(sf::Vector2f(0,0));
}

void QuickText::setPos(sf::Vector2f pos)
{
	text.setPosition(pos);
}
void QuickText::setString(std::string string)
{
	text.setString(string);
}
void QuickText::setSize(int size)
{
	text.setCharacterSize(size);
}
void QuickText::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void QuickText::draw(sf::RenderWindow &window)
{
	window.draw(text);
}*/