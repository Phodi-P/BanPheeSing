#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

//Global setting variables
const int WindowWidth = 1920;
const int WindowHeight = 1080;
const int RoomWidth = 1920;
const int RoomHeight = 1080;

namespace CUt //CUt is short for Custom Utility
{
	//***[Note] This function returns sign of value (-1,0,1) [Note]***
	template <typename T>
	T sign(T input)
	{
		return (T(0) < input) - (input < T(0));
	}
}

sf::Vector2f getViewOffset(sf::View &view)
{
	return view.getCenter() - sf::Vector2f(WindowWidth / 2, WindowHeight / 2);
}