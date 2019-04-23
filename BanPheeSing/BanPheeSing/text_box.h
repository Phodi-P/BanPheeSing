#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"
#include <vector>

class TextDiaglogue
{
public:
	std::string speakerName;
	std::string inputString;
	std::string ImgDir;
	sf::Font font;
	sf::Color speakerColor;

	TextDiaglogue(std::string, std::string, std::string, sf::Font, sf::Color);
	TextDiaglogue(std::string, std::string, sf::Font);
	TextDiaglogue();
};

TextDiaglogue::TextDiaglogue()
{
	//Default
}
TextDiaglogue::TextDiaglogue(std::string speakerName, std::string inputString, std::string ImgDir, sf::Font font, sf::Color speakerColor)
{
	this->speakerName = speakerName;
	this->inputString = inputString;
	this->ImgDir = ImgDir;
	this->font = font;
	this->speakerColor = speakerColor;
}

TextDiaglogue::TextDiaglogue(std::string speakerName, std::string inputString, sf::Font font)
{
	this->speakerName = speakerName;
	this->inputString = inputString;
	this->font = font;
	//Characters specific
	if (speakerName == "เอ")
	{
		this->ImgDir = ".//textures//portraits//a.png";
		this->speakerColor = sf::Color::Blue;
	}
	if (speakerName == "เขียว")
	{
		this->ImgDir = ".//textures//portraits//green.png";
		this->speakerColor = sf::Color::Green;
	}
	if (speakerName == "แดง")
	{
		this->ImgDir = ".//textures//portraits//red.png";
		this->speakerColor = sf::Color::Red;
	}
	if (speakerName == "ก้อย")
	{
		this->ImgDir = ".//textures//portraits//koy.png";
		this->speakerColor = sf::Color::Magenta;
	}
}


class TextBox
{
public:
	bool isDisplay = false;

	TextBox();
	TextBox(std::string, std::string, std::string, sf::Font);

	void setView(sf::View &);
	void setMargin(int);
	void setHeight(int);
	void setFont(sf::Font);
	void setStrings(std::string, std::string);
	void setImg(std::string);
	void setColor(sf::Color);

	void setDialogue(TextDiaglogue);
	void addDialogue(TextDiaglogue);


	void Continue();

	void updatePosition();
	void draw(sf::RenderWindow &window);

private:
	int textboxMargin = 15;
	int textboxHeight = 400;
	int textPerLine = 85;

	bool hasView = false;

	std::vector<TextDiaglogue> diagQueue;

	sf::Font font;
	std::string speakerName;
	std::string inputString;
	std::string displayString;
	std::string ImgDir = "";

	sf::Color speakerColor = sf::Color::Red;

	sf::RectangleShape box;
	sf::Text text_speaker;
	sf::Text text;
	sf::Text ContinueText;
	sf::Texture ImgTexture;
	sf::Sprite Img;
	sf::View *view;

	sf::Vector2f Offset = sf::Vector2f(0,0);

	void updateSetting();
	void calculateString();
};

TextBox::TextBox()
{
	isDisplay = false;

	ContinueText.setFont(font);
	ContinueText.setString("คลิกซ้าย หรือ กดสเปสบาร์ เพื่อไปต่อ");
	ContinueText.setCharacterSize(53);
	//ContinueText.setFillColor(sf::Color(0,0,0,125));
	ContinueText.setFillColor(sf::Color::Black);
}

TextBox::TextBox(std::string name, std::string textInput, std::string ImgDirInput, sf::Font fontInput)
{
	speakerName = name;
	inputString = textInput;
	ImgDir = ImgDirInput;
	font = fontInput;

	updateSetting();

	ContinueText.setFont(font);
	ContinueText.setString("คลิกซ้าย หรือ กดสเปสบาร์ เพื่อไปต่อ");
	ContinueText.setCharacterSize(53);
	//ContinueText.setFillColor(sf::Color(0,0,0,125));
	ContinueText.setFillColor(sf::Color::Black);

	isDisplay = true;
}

void TextBox::setDialogue(TextDiaglogue input)
{
	speakerName = input.speakerName;
	inputString = input.inputString;
	ImgDir = input.ImgDir;
	font = input.font;
	speakerColor = input.speakerColor;

	updateSetting();
	isDisplay = true;
}

void TextBox::setView(sf::View &view)
{
	this->view = &view;
	hasView = true;
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
	if (hasView) Offset = view->getCenter();
	else Offset = sf::Vector2f(0, 0);

	box.setPosition(sf::Vector2f(Offset.x+0, Offset.y+WindowHeight - textboxHeight));
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

	text.setPosition(Offset.x+textboxMargin, Offset.y+WindowHeight - textboxHeight + 120);

	if (ImgDir != "")
	{
		if (!ImgTexture.loadFromFile(ImgDir))
		{
			std::cerr << "Error: Cannot find player's texture\n";

			ImgTexture.loadFromFile(".\\textures\\missing_error.png");
		}
		Img.setTexture(ImgTexture);
		Img.setPosition(Offset.x,Offset.y+WindowHeight - textboxHeight-700);
	}
		text_speaker.setPosition(Offset.x+textboxMargin, Offset.y+WindowHeight - textboxHeight + textboxMargin);
}

void TextBox::updatePosition()
{
	if (hasView) Offset = view->getCenter();
	else Offset = sf::Vector2f(0, 0);

	box.setPosition(sf::Vector2f(Offset.x - WindowWidth / 2, Offset.y - WindowHeight / 2 + WindowHeight - textboxHeight));
	text.setPosition(Offset.x + textboxMargin - WindowWidth / 2, Offset.y - WindowHeight / 2 + WindowHeight - textboxHeight + 120);
	Img.setPosition(Offset.x - WindowWidth / 2, Offset.y - WindowHeight / 2 + WindowHeight - textboxHeight - 700);
	text_speaker.setPosition(Offset.x - WindowWidth / 2 + textboxMargin, Offset.y - WindowHeight / 2 + WindowHeight - textboxHeight + textboxMargin);

	ContinueText.setPosition(Offset.x - WindowWidth / 2 + textboxMargin+1250, Offset.y - WindowHeight / 2 + WindowHeight - textboxHeight + textboxMargin+250);

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
		if (curLineCount >= textPerLine)
		{
			curLineCount = 0;
			displayString += '\n';
		}
	}
}

void TextBox::setMargin(int margin)
{
	textboxMargin = margin;
}
void TextBox::setHeight(int height)
{
	textboxHeight = height;
}
void TextBox::setFont(sf::Font FontIn)
{
	font = FontIn;
}

void TextBox::addDialogue(TextDiaglogue diag)
{
	diagQueue.push_back(diag);
}

void TextBox::Continue()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		if (diagQueue.size() > 0)
		{
			isDisplay = true;
			setDialogue(diagQueue[0]);
			diagQueue.erase(diagQueue.begin());
		}
		else
		{
			diagQueue.clear();
			isDisplay = false;
		}
	}
}

void TextBox::draw(sf::RenderWindow &window)
{
	if (isDisplay)
	{
		if (ImgDir != "") window.draw(Img);
		window.draw(box);
		window.draw(text_speaker);
		window.draw(text);
		window.draw(ContinueText);
	}

}
