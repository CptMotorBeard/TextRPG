#pragma once
#include "BaseIncludes.h"
#include "Stats.h"
#include "HealthStats.h"

class UnitStatus
{
public:
	std::map<AttributeType, Attribute> UnitAttributes;
	std::map<SkillType, Skill> UnitSkills;

	HealthStats UnitHealth;

	UnitStatus() : UnitStatus(0) {};
	UnitStatus(uint16 startingAge);
};