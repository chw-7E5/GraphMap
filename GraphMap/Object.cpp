#include "Object.h"
#include <string>

int Object::current_id = 0;
Object::Object() : id(current_id++){}

int Object::getId()
{
	return id;
}
