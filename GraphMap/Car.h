#pragma once

#include "Vehicle.h"




class Car :
    public Vehicle
{
public:
    
    Car(float speed, float maxfuel);
    int getType();
};

