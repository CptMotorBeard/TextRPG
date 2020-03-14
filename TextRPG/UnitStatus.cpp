#include "UnitStatus.h"
const AttributeType Attribute::AllAttributes[] = {
	AttributeType::Strength,
	AttributeType::Dexterity,
	AttributeType::Constitution,
	AttributeType::Intelligence,
	AttributeType::Wisdom,
	AttributeType::Charisma
};

std::string Attribute::AttributeString(AttributeType type)
{
	switch (type)
	{
	case AttributeType::Strength:
		return "Strength";
	case AttributeType::Dexterity:
		return "Dexterity";
	case AttributeType::Constitution:
		return "Constitution";
	case AttributeType::Intelligence:
		return "Intelligence";
	case AttributeType::Wisdom:
		return "Wisdom";
	case AttributeType::Charisma:
		return "Charisma";
	default:
		return "";
	}
}

const SkillType Skill::AllSkills[] = {
	SkillType::Test
};

std::string Skill::SkillString(SkillType type)
{
	return "";
}

UnitStatus::UnitStatus()
{
	for (auto att : Attribute::AllAttributes)
	{
		UnitStatus::UnitAttributes.insert(std::pair<AttributeType, Attribute> (att, Attribute(att)));
	}

	for (auto skill : Skill::AllSkills)
	{
		UnitStatus::UnitSkills.insert(std::pair<SkillType, Skill>(skill, Skill(skill)));
	}
}