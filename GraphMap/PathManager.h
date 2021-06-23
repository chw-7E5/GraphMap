#pragma once
#include "PlaceManager.h"

class PathManager
{
private:
	PlaceManager& placeManager;
public:
	PathManager(PlaceManager& placeManager);

	bool move(int startint, int endint, Person& person);
};

