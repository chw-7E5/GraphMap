#pragma once
#include "PlaceManager.h"

class ObjectManager
{
private:
	PlaceManager &placeManager;
	std::vector<Person*> personList;

public:
	ObjectManager(PlaceManager &);

	const std::vector<Person*>& getPersonList() const;

	const Person* getPerson(int target) const;
	bool deletePerson(int target);
	bool addPerson(std::string name, float speed, int placeInt);

};

