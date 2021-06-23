#include "Vehicle.h"



Vehicle::Vehicle(float speed, float MAX_FUEL)
    : speed(speed), MAX_FUEL(MAX_FUEL) {
}

bool Vehicle::setFuelBy(float fuel)
{
    float target = this->fuel + fuel;
    if (target >= 0) {
        fuel = target;
        return true;
    }else return false;
}

