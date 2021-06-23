#pragma once
class Object
{
private:
	static int current_id;
	int id;
public:
	Object();
	int getId();
};

