#include "UnitStatus.h"

UnitStatus::UnitStatus(uint16 startingAge)
{
	UnitStatus::UnitHealth = HealthStats(startingAge);

	for (auto iter: Attribute::AllAttributes)
	{
		AttributeType att = iter.first;
		UnitStatus::UnitAttributes.insert(std::pair<AttributeType, Attribute> (att, Attribute(att)));		
	}

	for (auto iter: Skill::AllSkills)
	{
		SkillType skill = iter.first;
		UnitStatus::UnitSkills.insert(std::pair<SkillType, Skill>(skill, Skill(skill)));
	}
}