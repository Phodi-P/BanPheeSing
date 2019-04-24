#pragma once

#include "custom_utility.h"
#include <set>

class Event
{
public:
	Event();

	void triggerEvent(std::string);
	bool checkEvent(std::string);
	bool checkTriggeredEvent(std::string);

	std::string getLastEvent();
	void clearEvent();

private:
	std::set<std::string> id;
	std::set<std::string> id_triggered;
	std::string lastEvent;
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
			lastEvent = *i;
			this->id_triggered.insert(*i);
			this->id.erase(i);
			return true;
		}
	}
	return false;
}

bool Event::checkTriggeredEvent(std::string id)
{
	std::set<std::string>::iterator i;
	for (i = this->id_triggered.begin(); i != this->id_triggered.end(); ++i)
	{
		if (*i == id)
		{
			this->id_triggered.erase(i);
			return true;
		}
	}
	return false;
}

std::string Event::getLastEvent()
{
	return lastEvent;
}

void Event::clearEvent()
{
	this->id.clear();
}