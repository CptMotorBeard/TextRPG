#pragma once
#include "Inventory.h"
#include "UnitStatus.h"
#include "UnitTraits.h"

class Unit
{
private:
	uint8 mHeight;
	uint8 mWeight;

public:
	std::string Name;
	UnitStatus Status;
	std::vector<UnitTraits> Traits;

	Inventory UnitInventory;

	Unit() : Unit(0, 0, 0) {};
	Unit(uint16 startingAge, uint8 startingHeight, uint8 startingWeight);
};

class Leader : public Unit
{
public:
	Leader() : Leader(0, 0, 0) {};
	Leader(uint16 startingAge, uint8 startingHeight, uint8 startingWeight) : Unit(startingAge, startingHeight, startingWeight) {};
};