#include "Person.h"

Person::Person(std::string name, float speed) : name(name), speed(speed)
{
}

Person::~Person()
{
}

const std::string& Person::getName() const
{
    return name;
}


