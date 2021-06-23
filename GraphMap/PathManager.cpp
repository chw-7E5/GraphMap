#include "PathManager.h"

PathManager::PathManager(PlaceManager& placeManager) : placeManager(placeManager)
{
}

bool PathManager::move(int startint, int endint, Person &person)
{
	Place *start = placeManager.findPlace(startint);
	Place* end = placeManager.findPlace(endint);

	// Check if route exist
	auto lookFor = [&](std::pair<Place*,float> current) {return current.first->getId() == end->getId(); };
	auto it = std::find_if(start->nearby.begin(), start->nearby.end(), lookFor);
	if (it != std::end(start->nearby)) {
		// If route exists
		placeManager.removePersonFrom(startint, person.getId());
		placeManager.addPerson(endint, &person);
		return true;
	}
	return false;
}
