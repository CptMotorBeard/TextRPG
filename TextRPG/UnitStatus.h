#pragma once
#include "BaseIncludes.h"
#include "Stats.h"

class UnitStatus
{
public:
	std::map<AttributeType, Attribute> UnitAttributes;
	std::map<SkillType, Skill> UnitSkills;

	UnitStatus();
};