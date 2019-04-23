#pragma once

#include "custom_utility.h"
#include <list>

class Event
{
public:
	Event();

	std::list<std::string> id;
	void triggerEvent(std::string);
	bool checkEvent(std::string);
	void clearEvent();
};
Event::Event()
{
	//Default
}

void Event::triggerEvent(std::string id)
{
	this->id.push_back(id);
	//Need unique function to check if event id is already inside the list
}

bool Event::checkEvent(std::string id)
{
	std::list<std::string>::iterator i;
	for (i = this->id.begin(); i != this->id.end(); ++i)
	{
		if (*i == id)
		{
			this->id.erase(i);
			return true;
		}
	}
	return false;
}

void Event::clearEvent()
{
	this->id.clear();
}