#pragma once

#include <iostream>
#include <string>
#include <cmath>

class CUt
{
public:
	template <typename T>
	T sign(T input);
};

template <typename T>
T CUt::sign(T input)
{
	return (T(0) < input) - (input < T(0));
}