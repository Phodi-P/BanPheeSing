#pragma once

#include "custom_utility.h"
#include <set>

class Event
{
public:
	Event();

	std::set<std::string> id;
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
	this->id.insert(id);
}

bool Event::checkEvent(std::string id)
{
	std::set<std::string>::iterator i;
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