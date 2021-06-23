#pragma once

#include <vector>
#include <string>

#include "Person.h"
#include "Vehicle.h"

class Place :
	public Object
{
private:
	std::vector<Vehicle*> inventory;
	std::vector<Person*> people;
	std::string name;
	std::vector<std::pair<Place*,float>> nearby;

	friend class PlaceManager;
	friend class ObjectManager;
	friend class PathManager;
public:
	Place(std::string name);

	std::string getName() const;
	const std::vector<Vehicle*>& getInventory() const;
	const std::vector<Person*>& getPeople() const;
	const std::vector<std::pair<Place*, float>>& getNearby() const;
};

