#include "Unit.h"

Unit::Unit(uint16 startingAge, uint8 startingHeight, uint8 startingWeight)
{
	Unit::Name = "";

	Unit::Status = UnitStatus(startingAge);

	Unit::mHeight = startingHeight;
	Unit::mWeight = startingWeight;
}