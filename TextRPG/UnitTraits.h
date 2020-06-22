#pragma once
#include "BaseIncludes.h"

enum class PersonalityTraits
{
	LENGTH
};

class UnitTraits
{
public:
	json SerializeData() const { json data; return data; };
	void DeserializeData(json data) {};
};