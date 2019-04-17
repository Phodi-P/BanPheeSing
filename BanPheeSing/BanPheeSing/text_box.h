#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"
#include <vector>


class TextBox
{
public:
	bool isDisplay = false;

	TextBox();
	TextBox(std::string, std::string, std::string, sf::Font);

	void setMargin(int);
	void setHeight(int);
	void setFont(sf::Font);
	void setStrings(std::string, std::string);
	void setImg(std::string);
	void setColor(sf::Color);

	void checkContinue();

	void draw(sf::RenderWindow &window);

private:
	int textboxMargin = 15;
	int textboxHeight = 400;
	int textPerLine = 85;

	sf::Font font;
	std::string speakerName;
	std::string inputString;
	std::string displayString;
	std::string ImgDir = "";

	sf::Color speakerColor = sf::Color::Red;

	sf::RectangleShape box;
	sf::Text text_speaker;
	sf::Text text;
	sf::Texture ImgTexture;
	sf::Sprite Img;

	void updateSetting();
	void calculateString();

	const int WindowWidth = 1920;
	const int WindowHeight = 1080;
};

TextBox::TextBox()
{
	isDisplay = false;
}

TextBox::TextBox(std::string name, std::string textInput, std::string ImgDirInput, sf::Font fontInput)
{
	speakerName = name;
	inputString = textInput;
	ImgDir = ImgDirInput;
	font = fontInput;

	updateSetting();
	isDisplay = true;
}

void TextBox::setColor(sf::Color color)
{
	speakerColor = color;
	updateSetting();
}

void TextBox::setStrings(std::string name = "NULL", std::string textInput = "NULL")
{
	if(speakerName != "NULL") speakerName = name;
	if(inputString != "NULL") inputString = textInput;

	updateSetting();
}

//Standard Portrait is 700x700
void TextBox::setImg(std::string ImgDir)
{
	this->ImgDir = ImgDir;
	updateSetting();
}

void TextBox::updateSetting()
{
	box.setPosition(sf::Vector2f(0, WindowHeight - textboxHeight));
	box.setSize(sf::Vector2f(WindowWidth, textboxHeight));

	text_speaker.setFont(font);
	text_speaker.setString(speakerName);
	text_speaker.setCharacterSize(72);
	text_speaker.setFillColor(speakerColor);
	text_speaker.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setFont(font);

	calculateString();

	text.setCharacterSize(48);
	text.setFillColor(sf::Color::Black);

	text.setPosition(textboxMargin, WindowHeight - textboxHeight + 120);

	if (ImgDir != "")
	{
		if (!ImgTexture.loadFromFile(ImgDir))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			ImgTexture.loadFromFile(".\\textures\\missing_error.png");
		}
		Img.setTexture(ImgTexture);
		Img.setPosition(0,WindowHeight - textboxHeight-700);
	}
		text_speaker.setPosition(textboxMargin, WindowHeight - textboxHeight + textboxMargin);
}

void TextBox::calculateString()
{
	//Perform textwrap etc...
	displayString = "";
	int curLineCount = 0;
	for (int i = 0; i < inputString.size(); i++)
	{
		displayString += inputString[i];
		text.setString(displayString);
		curLineCount++;
		std::cout << curLineCount << "\n";
		if (curLineCount >= textPerLine)
		{
			curLineCount = 0;
			displayString += '\n';
			std::cout << "Newline\n";
		}
	}
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

void TextBox::checkContinue()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isDisplay) isDisplay = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isDisplay) isDisplay = false;
}

void TextBox::draw(sf::RenderWindow &window)
{
	if (isDisplay)
	{
		if (ImgDir != "") window.draw(Img);
		window.draw(box);
		window.draw(text_speaker);
		window.draw(text);
	}

}
