#include "Stats.h"
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

template<typename E>
Stat<E>::Stat(E statType, uint16 startingValue)
{
	mStatType = statType;
	mBaseValue = startingValue;
	mModifiers = std::vector<int8>();
};

template<typename E>
int16 Stat<E>::GetTotalModifier()
{
	int16 total = 0;
	for (auto attributeModifier : Stat::mModifiers)
	{
		total += attributeModifier;
	}
}

template<typename E>
const uint16& Stat<E>::GetBaseValue()
{
	return mBaseValue;
}

template<typename E>
uint16 Stat<E>::GetValue()
{
	int16 modifier = GetTotalModifier();
	if (modifier > mBaseValue)
	{
		return 0;
	}

	return mBaseValue - modifier;
}

template<typename E>
uint16 Stat<E>::AddModifier(int8 modifier)
{
	mModifiers.push_back(modifier);
	return GetValue();
}