#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "custom_utility.h"
#include <vector>

class ObjSpawn
{
public:
	ObjSpawn();
	~ObjSpawn();

protected:
	std::vector<*Obj> allObjPtr;
};