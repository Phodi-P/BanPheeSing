#pragma once

#include <iostream>
#include <string>
#include <cmath>

namespace CUt //CUt is short for Custom Utility
{
	//***[Note] This function returns sign of value (-1,0,1) [Note]***
	template <typename T>
	T sign(T input)
	{
		return (T(0) < input) - (input < T(0));
	}
}