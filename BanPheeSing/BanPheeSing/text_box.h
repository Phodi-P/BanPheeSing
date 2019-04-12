#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"
#include <vector>


class TextBox
{
public:
	TextBox(std::string, std::string, std::string, sf::Font, bool);

	void setSide(std::string);
	void setSide(bool);

	void setMargin(int);
	void setHeight(int);
	void setFont(sf::Font);

	void draw(sf::RenderWindow &window);

private:
	bool isOnLeftSide = true;
	int textboxMargin = 15;
	int textboxHeight = 400;

	sf::Font font;
	std::string speakerName;
	std::string inputString;
	std::string displayString;
	std::string ImgDir;

	sf::RectangleShape box;
	sf::Text text_speaker;
	sf::Text text;

	void updateSetting();
	void calculateString();

	const int WindowWidth = 1920;
	const int WindowHeight = 1080;
};

TextBox::TextBox(std::string name, std::string textInput, std::string ImgDirInput, sf::Font fontInput, bool side = true)
{
	speakerName = name;
	inputString = textInput;
	ImgDir = ImgDirInput;
	font = fontInput;
	isOnLeftSide = side;

	updateSetting();
}

void TextBox::updateSetting()
{
	box.setPosition(sf::Vector2f(0, WindowHeight - textboxHeight));
	box.setSize(sf::Vector2f(WindowWidth, textboxHeight));

	text_speaker.setFont(font);
	text_speaker.setString(speakerName);
	text_speaker.setCharacterSize(72);
	text_speaker.setFillColor(sf::Color::Red);
	text_speaker.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setFont(font);

	calculateString();
	text.setString(displayString);

	text.setCharacterSize(48);
	text.setFillColor(sf::Color::Black);

	text.setPosition(textboxMargin, WindowHeight - textboxHeight + 120);

	if (isOnLeftSide) text_speaker.setPosition(textboxMargin, WindowHeight - textboxHeight + textboxMargin);
	else text_speaker.setPosition(WindowWidth - text_speaker.getGlobalBounds().width - 15 - textboxMargin, WindowHeight - textboxHeight + textboxMargin);
}

void TextBox::calculateString()
{
	//Perform textwrap etc...
	displayString = inputString;
}

void TextBox::setSide(std::string side)
{
	if (side == "left") isOnLeftSide = true;
	else if (side == "right") isOnLeftSide = false;
	updateSetting();
}
void TextBox::setSide(bool side)
{
	isOnLeftSide = side;
	updateSetting();
}

void TextBox::setMargin(int margin)
{
	textboxMargin = margin;
	updateSetting();
}
void TextBox::setHeight(int height)
{
	textboxHeight = height;
	updateSetting();
}
void TextBox::setFont(sf::Font FontIn)
{
	font = FontIn;
	updateSetting();
}

void TextBox::draw(sf::RenderWindow &window)
{
	window.draw(box);
	window.draw(text_speaker);
	window.draw(text);
}
