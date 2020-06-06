#pragma once
#include "BaseIncludes.h"

#include "HealthStats.h"
#include "Stats.h"

class UnitStatus
{
public:
	std::map<AttributeType, Attribute> UnitAttributes;
	std::map<SkillType, Skill> UnitSkills;

	HealthStats UnitHealth;

	UnitStatus() : UnitStatus(0) {};
	UnitStatus(uint16 startingAge);
};