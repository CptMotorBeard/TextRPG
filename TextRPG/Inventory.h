#pragma once
#include "BaseIncludes.h"

class Inventory
{
public:
	json SerializeData() const { json data; return data; };
	void DeserializeData(json data) {};
};