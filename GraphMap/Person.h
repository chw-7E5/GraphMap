#pragma once

#include <vector>
#include <string>

#include "Object.h"

class Person :
	public Object
{
private:
	std::string name;
	float speed;

public:
	Person(std::string name, float speed);
	~Person();

	const std::string &getName() const;

};

