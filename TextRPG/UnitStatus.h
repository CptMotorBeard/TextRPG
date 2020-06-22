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
	UnitStatus(const uint16& startingAge);

	json SerializeData() const;
	void DeserializeData(json data);
};