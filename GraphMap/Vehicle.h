#pragma once

#include <map>
#include <string>

#include "Object.h"

class Vehicle :
    public Object
{
protected:
    float speed;
    float fuel;
    const float MAX_FUEL;

public:
    // Enum of possible Vehicles
    enum vehTypes {car,ship,plane};

    Vehicle(float speed,float MAX_FUEL);

    // Change value of refuel, can pass negivate but the total fuel cannot be negivate
    // 1 distance = 1 fuel
    bool setFuelBy(float fuel); 

    // Get type of vehicle
    virtual int getType() = 0;
    
};

