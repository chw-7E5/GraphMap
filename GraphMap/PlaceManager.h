#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "Place.h"

class PlaceManager
{
private:
	int numOfplaces;
	std::vector<Place*> placeList;

	// Return a Place with name or id
	Place * findPlace(const std::string&);
	Place * findPlace(int);

	friend class ObjectManager;
	friend class PathManager;
public:
	PlaceManager();
	~PlaceManager();

	// Function to spawn a vehicle (within a location)
	
	bool addPlace(std::vector<std::string> name);
	bool deletePlace(int id);
	// Connect two Places
	bool connect(int start, int end, float distance);
	bool connect(Place & start, Place & end, float distance);

	// Place object management
	bool addToInventory(int placeInt, Vehicle* target);
	// Remove vehicle with the id
	bool removeFromInventory(int placeInt, int target);

	bool addPerson(int placeInt, Person* target);
	bool removePersonFrom(int placeInt, int target);

	// Places
	const std::vector<Place*>& getPlaceList();

	// Return a Place with name or id
	const Place* getPlace(const std::string&);
	const Place* getPlace(int);

	// Misc
	int matTrans(int x, int y);
	
};

