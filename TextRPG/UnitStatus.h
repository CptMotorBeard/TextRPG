#pragma once
#include "BaseIncludes.h"

enum class AttributeType
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma
};

enum class SkillType
{
	Test
};

class Attribute
{
private:
	AttributeType mAttributeType;
	uint16 mBaseValue;
	std::vector<int8> mAttributeModifiers;	

public:
	static const AttributeType AllAttributes[];
	static std::string AttributeString(AttributeType type);

	Attribute(AttributeType attributeType)
	{
		mAttributeType = attributeType;
		mBaseValue = 10;
		mAttributeModifiers = std::vector<int8>();
	}	

	int16 GetTotalModifier()
	{
		int16 total = 0;
		for (auto attributeModifier : mAttributeModifiers)
		{
			total += attributeModifier;
		}
	}

	uint16 GetValue()
	{
		int16 modifier = GetTotalModifier();
		if (modifier > mBaseValue)
		{
			return 0;
		}

		return mBaseValue - modifier;
	}

	uint16 AddModifier(int8 modifier)
	{
		mAttributeModifiers.push_back(modifier);
		return GetValue();
	}
};

class Skill
{
private:
	SkillType mSkillType;
	uint16 mBaseValue;
	std::vector<int8> mSkillModifiers;

public:
	static const SkillType AllSkills[];
	static std::string SkillString(SkillType type);

	Skill(SkillType skillType)
	{
		mSkillType = skillType;
		mBaseValue = 0;
		mSkillModifiers = std::vector<int8>();
	}
};

class UnitStatus
{
public:
	std::map<AttributeType, Attribute> UnitAttributes;
	std::map<SkillType, Skill> UnitSkills;

	UnitStatus();
};