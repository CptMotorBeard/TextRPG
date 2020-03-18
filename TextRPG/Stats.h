#pragma once
#include "BaseIncludes.h"

template <typename E>
class Stat
{
	static_assert(std::is_enum<E>::value, "Type E must be an enum");
private:
	E mStatType;
	uint16 mBaseValue;
	std::vector<int8> mModifiers;

public:
	Stat(E statType, uint16 startingValue)
	{
		mStatType = statType;
		mBaseValue = startingValue;
		mModifiers = std::vector<int8>();
	};

	int16 GetTotalModifier()
	{
		int16 total = 0;
		for (auto attributeModifier : Stat::mModifiers)
		{
			total += attributeModifier;
		}
	};

	const uint16& GetBaseValue()
	{
		return mBaseValue;
	};

	uint16 GetValue()
	{
		int16 modifier = GetTotalModifier();
		if (modifier > mBaseValue)
		{
			return 0;
		}

		return mBaseValue - modifier;
	};

	uint16 AddModifier(int8 modifier)
	{
		mModifiers.push_back(modifier);
		return GetValue();
	};
};

enum class AttributeType
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma,
	LENGTH
};

class Attribute : public Stat<AttributeType>
{
public:
	static const AttributeType AllAttributes[(int)AttributeType::LENGTH];
	static std::string AttributeString(AttributeType type);

	Attribute(AttributeType attributeType) : Stat(attributeType, 10) {};
};

enum class SkillType
{
	Test,
	LENGTH
};

class Skill : public Stat<SkillType>
{
public:
	static const SkillType AllSkills[(int)SkillType::LENGTH];
	static std::string SkillString(SkillType type);

	Skill(SkillType skillType) : Stat(skillType, 0) {};
};