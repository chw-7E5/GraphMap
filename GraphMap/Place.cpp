#include "Place.h"

Place::Place(std::string name) : name(name)
{
}

std::string Place::getName() const 
{
    return name;
}

const std::vector<Vehicle*>& Place::getInventory() const
{
    return inventory;
}

const std::vector<Person*>& Place::getPeople() const
{
    return people;
}

const std::vector<std::pair<Place*, float>>& Place::getNearby() const
{
    return nearby;
}
