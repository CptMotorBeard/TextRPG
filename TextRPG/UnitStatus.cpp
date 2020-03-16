#include "UnitStatus.h"

UnitStatus::UnitStatus(uint16 startingAge)
{
	UnitHealth = HealthStats(startingAge);

	for (auto att : Attribute::AllAttributes)
	{
		UnitStatus::UnitAttributes.insert(std::pair<AttributeType, Attribute> (att, Attribute(att)));		
	}

	for (auto skill : Skill::AllSkills)
	{
		UnitStatus::UnitSkills.insert(std::pair<SkillType, Skill>(skill, Skill(skill)));
	}
}