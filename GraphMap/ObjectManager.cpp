#include "ObjectManager.h"

const Person* ObjectManager::getPerson(int target) const {
	auto lookFor = [&](Person* current) {return current->getId() == target; };
	auto it = find_if(personList.begin(), personList.end(), lookFor);
	if (it != std::end(personList)) {
		const Person* tmp = *it;
		return tmp;
	}else return nullptr;
}

ObjectManager::ObjectManager(PlaceManager& placeManager) : placeManager(placeManager)
{
}

const std::vector<Person*>& ObjectManager::getPersonList() const {
	return personList;
}

bool ObjectManager::deletePerson(int target) {
	auto lookFor = [&](Person* current) {return current->getId() == target; };
	auto it = find_if(personList.begin(), personList.end(), lookFor);
	if (it != std::end(personList)) {
		delete* it;
		personList.erase(it);
		return true;
	}else return false;
}

bool ObjectManager::addPerson(std::string name, float speed, int placeInt) {

	Place* place = placeManager.findPlace(placeInt);
	if (!place)
		return false;

	auto lookFor = [&](Person* current) {return current->getName() == name; };
	auto it = find_if(personList.begin(), personList.end(), lookFor);
	if (it == std::end(personList)) {
		Person* tmp = new Person(name, speed);
		personList.push_back(tmp);
		place->people.push_back(tmp);
		return true;
	}
	else return false;
}