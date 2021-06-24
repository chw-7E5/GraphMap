#include <iostream>
#include "PlaceManager.h"
#include "ObjectManager.h"
#include "PathManager.h"

//Input validation
float numInput() {
	float input;
	while (!(std::cin >> input) || input < 0) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invaild Input! Please try again: ";
	}
	std::cin.ignore(1000, '\n');
	return input;
}

std::string stringInput() {
	std::string input;
	while (!(std::cin >> input)) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invaild Input! Please try again: ";
	}
	std::cin.ignore(1000, '\n');
	return input;
}

void testFunction() {
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
	for (Place* place : placeManager.getPlaceList())
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



	Person& bob = *objectManager.getPersonList()[0];

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

}

int main() {
	
	if (numInput() != 0) {
		testFunction();
		return 0;
	}

	PlaceManager placeManager;
	ObjectManager objectManager(placeManager);
	PathManager pathManager(placeManager);

	std::cout << "Enter the number of places: ";

	int numOfPlace = numInput();

	std::cout << std::endl;

	std::vector<std::string> tmp;
	tmp.reserve(numOfPlace);

	for (int i = 0; i < numOfPlace; i++)
		tmp.push_back(stringInput());

	placeManager.addPlace(tmp);
	bool end = false;
	do {
		system("CLS");
		{
			int index = 0;
			for (Place* place : placeManager.getPlaceList()) {
				std::cout << index++ << ". " << place->getName() << ":" << std::endl;
				for (auto nearby : place->getNearby()) {
					std::cout << nearby.first->getName() << ", distance: " << nearby.second << std::endl;
				}
				std::cout << std::endl;
			}
		}

		std::cout << std::endl;
		std::cout << "Please select a place: (999 to exit)" << std::endl;
		int input = numInput();
		switch (input) {
			case 999:
				end = true;
				break;
			case 1000:
				system("CLS");
				testFunction();
				break;
			default:
				// Choose which place
				while (input < 0 || input >= placeManager.getPlaceList().size()) {
					std::cout << "Invalid place: ";
					input = numInput();
				}
				int startInt = placeManager.getPlaceList()[input]->getId();
				// Choose which place to connect to
				std::cout << "Connecting to: " << std::endl;
				{
					int index = 0;
					for (Place* place : placeManager.getPlaceList()) {
						std::cout << index++ << ": " << place->getName() << std::endl;
					}
				}

				input = numInput();

				while (input <= 0 || input >= placeManager.getPlaceList().size()) {
					std::cout << "Invalid place: ";
					input = numInput();
				}
				int endInt = placeManager.getPlaceList()[input]->getId();

				// Ask for distance
				std::cout << "Distance: ";
				float distance = numInput();

				if (placeManager.connect(startInt, endInt, distance)) {
					std::cout << "Connected" << std::endl;
				}
				else {
					std::cout << "Connection failed" << std::endl;
				}

				break;
		}

	} while (!end);

	return 0;
}