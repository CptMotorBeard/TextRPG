#include "Unit.h"

Unit::Unit(const uint16& startingAge, const uint8& startingHeight, const uint8& startingWeight)
{
	Unit::Name = "";

	Unit::Status = UnitStatus(startingAge);

	Unit::mHeight = startingHeight;
	Unit::mWeight = startingWeight;
}