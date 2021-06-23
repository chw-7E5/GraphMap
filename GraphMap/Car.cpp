#include "Car.h"

Car::Car(float speed, float MAX_FUEL) : Vehicle(speed, MAX_FUEL) {
	fuel = MAX_FUEL;
}

int Car::getType()
{
	return car;
}
