#include <iostream>
#include "PlaceManager.h"
#include "ObjectManager.h"
#include "PathManager.h"

int main() {
	PlaceManager placeManager;
	ObjectManager objectManager(placeManager);
	PathManager pathManager(placeManager);

	std::vector<std::string> tmp;
	tmp.reserve(3);
	tmp.push_back("HK");
	tmp.push_back("NY");
	tmp.push_back("DC");


	placeManager.addPlace(tmp);

	std::cout << "towns: " << std::endl;
	for (Place *place : placeManager.getPlaceList())
		std::cout << place->getName() << " " << place->getId() << std::endl;
	std::cout << std::endl;

	placeManager.connect(0, 1, 1);
	placeManager.connect(0, 2, 2);
	placeManager.connect(1, 2, 1);

	std::cout << placeManager.getPlaceList()[1]->getName() << ": " << std::endl;
	for (auto place : placeManager.getPlaceList()[1]->getNearby())
		std::cout << place.first->getName() << " - " << place.second << std::endl;
	std::cout << std::endl;

	placeManager.deletePlace(0);
	std::cout << "Deleting" << std::endl;
	std::cout << std::endl;

	auto NY = placeManager.getPlaceList()[0];
	auto DC = placeManager.getPlaceList()[1];
	

	std::cout << NY->getName() << ": " << std::endl;
	for (auto place : NY->getNearby())
		std::cout << place.first->getName() << " - " << place.second << std::endl;
	std::cout << std::endl;

	objectManager.addPerson("bob", 1, NY->getId());
	std::cout << "NY: " << NY->getPeople()[0]->getName() << std::endl;
	std::cout << std::endl;

	Person &bob = *objectManager.getPersonList()[0];

	if (pathManager.move(NY->getId(), DC->getId(), bob)) {
		std::cout << "moved" << std::endl;
	}
	else {
		std::cout << "move failed" << std::endl;
	}

	std::cout << "DC: " << DC->getPeople()[0]->getName() << std::endl;
	std::cout << std::endl;
	placeManager.removePersonFrom(DC->getId(), bob.getId());
	std::cout << "DC size " << DC->getPeople().size() << std::endl;

	return 0;
}