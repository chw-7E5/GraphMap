#include "PlaceManager.h"
#include <iostream>
#include "Car.h"

PlaceManager::PlaceManager()
{
	numOfplaces = 0;
}

PlaceManager::~PlaceManager()
{
}

bool PlaceManager::addPlace(std::vector<std::string> places)
{
	numOfplaces += places.size();
	for (std::string name : places) {
		Place* ptr = new Place(name);
		placeList.push_back(ptr);
	}
	return true;
}

bool PlaceManager::deletePlace(int id)
{
	// Find the target
	auto lookFor = [&](Place *current) {return current->getId() == id; };
	auto place = find_if(placeList.begin(), placeList.end(), lookFor);
	// If target exists
	if (place != std::end(placeList)) {
		// Get nearby places
		for (auto near : (*place)->nearby) {
			// Remove references of the target in nearby places
			auto lookForPair = [&](auto current) {return current.first->getId() == id; };
			auto target =
				find_if(near.first->nearby.begin(), near.first->nearby.end(), lookForPair);
			auto tmp = near.first->nearby[target-near.first->nearby.begin()];

			if(target != std::end(near.first->nearby))
				near.first->nearby.erase(target);
		}

		// Remove target
		delete *place;
		placeList.erase(place);
		return true;
	}
	else {
		return false;
	}
}

bool PlaceManager::addToInventory(int placeInt, Vehicle* target)
{
	Place* place = findPlace(placeInt);
	if (!place)
		return false;

	auto lookFor = [&](Vehicle* current) {return current->getId() == target->getId(); };
	auto it = find_if(place->inventory.begin(), place->inventory.end(), lookFor);
	if (it != std::end(place->inventory)) {
		place->inventory.push_back(target);
		return true;
	}
	else
		return false;
}

bool PlaceManager::removeFromInventory(int placeInt, int target)
{
	Place* place = findPlace(placeInt);
	if (!place)
		return false;
	
	auto lookFor = [&](Vehicle* current) {return current->getId() == target; };
	auto it = find_if(place->inventory.begin(), place->inventory.end(), lookFor);
	if (it != std::end(place->inventory)) {
		place->inventory.erase(it);
		return true;
	}
	else 
		return false;
}

bool PlaceManager::addPerson(int placeInt, Person *target)
{
	Place* place = findPlace(placeInt);
	if (!place)
		return false;

	auto lookFor = [&](Person* current) {return current->getId() == target->getId(); };
	auto it = find_if(place->people.begin(), place->people.end(), lookFor);
	if (it == std::end(place->people)) {
		place->people.push_back(target);
		return true;
	}
	else
		return false;
}

bool PlaceManager::removePersonFrom(int placeInt, int target)
{
	Place* place = findPlace(placeInt);
	if (!place)
		return false;
	
	auto lookFor = [&](Person* current) {return current->getId() == target; };
	auto it = find_if(place->people.begin(), place->people.end(), lookFor);
	if (it != std::end(place->people)) {
		place->people.erase(it);
		return true;
	}
	else
		return false;
}

bool PlaceManager::connect(int start, int end, float distance) {
	Place *startPlace = findPlace(start);
	Place* endPlace = findPlace(end);
	if (startPlace && endPlace) {
		return connect(*startPlace, *endPlace, distance);
	}
	return false;
}

bool PlaceManager::connect(Place& start, Place& end, float distance)
{
	// Not the same place
	if (start.getId() == end.getId()) {
		return false;
	}
	// Check if path already exists
	auto lookFor = [&](auto current) {return current.first->getId() == end.getId(); };
	auto it = find_if(start.nearby.begin(), start.nearby.end(), lookFor);
	if (it == std::end(start.nearby)) {
		// If it doesnt exist
		start.nearby.emplace_back(&end, distance);
		end.nearby.emplace_back(&start, distance);
		return true;
	}
	else return false;
}

Place * PlaceManager::findPlace(const std::string& target)
{
	auto lookFor = [&](Place *current) {return current->getName() == target; };
	auto it = find_if(placeList.begin(), placeList.end(), lookFor);
	if (it != std::end(placeList)) {
		Place * tmp = *it;
		return tmp;
	}return nullptr;
}

Place * PlaceManager::findPlace(int target)
{
	auto lookFor = [&](Place *current) {return current->getId() == target; };
	auto it = find_if(placeList.begin(), placeList.end(), lookFor);
	if (it != std::end(placeList)) {
		Place * tmp = *it;
		return tmp;
	}return nullptr;
}

const Place* PlaceManager::getPlace(const std::string& target)
{
	auto lookFor = [&](Place *current) {return current->getName() == target; };
	auto it = find_if(placeList.begin(), placeList.end(), lookFor);
	if (it != std::end(placeList)) {
		const Place* tmp = *it;
		return tmp;
	}return nullptr;
}

const Place* PlaceManager::getPlace(int target)
{
	auto lookFor = [&](Place *current) {return current->getId() == target; };
	auto it = find_if(placeList.begin(), placeList.end(), lookFor);
	if (it != std::end(placeList)) {
		const Place* tmp = *it;
		return tmp;
	}return nullptr;
}

const std::vector<Place*>& PlaceManager::getPlaceList()
{
	return placeList;
}

int PlaceManager::matTrans(int x, int y)
{
	return x + numOfplaces * y;
}
