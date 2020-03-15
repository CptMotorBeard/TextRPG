#pragma once
#include "UnitStatus.h"
#include "UnitTraits.h"
#include "Inventory.h"

class Unit
{
public:
	UnitStatus Status;
	std::vector<UnitTraits> Traits;
	std::vector<PersonalityTraits> Personality;

	Inventory UnitInventory;

	uint8 Height;
	uint8 Weight;
};