#pragma once
#include "BaseIncludes.h"

#define ALL_STAT_MAP(enumType, stringValue, shortValue) { enumType :: stringValue, StatString(#stringValue, #shortValue)}

template <typename E>
class Stat
{
	static_assert(std::is_enum<E>::value, "Type E must be an enum");
private:
	E mStatType;
	uint16 mBaseValue;
	std::vector<int8> mModifiers;

public:
	Stat() {};
	Stat(const E &statType, uint16 startingValue)
	{
		mStatType = statType;
		mBaseValue = startingValue;
	};

	int16 GetTotalModifier()
	{
		int16 total = 0;
		for (auto const &attributeModifier : Stat::mModifiers)
		{
			total += attributeModifier;
		}

		return total;
	};

	const uint16& GetBaseValue()
	{
		return mBaseValue;
	};

	uint16 GetValue()
	{
		int16 modifier = GetTotalModifier();
		return mBaseValue + modifier;
	};

	uint16 AddModifier(int8 modifier)
	{
		mModifiers.push_back(modifier);
		return GetValue();
	};

	uint16 RemoveModifier(int8 modifier)
	{
		auto position = std::find(mModifiers.begin(), mModifiers.end(), modifier);
		if (position != mModifiers.end())
		{
			mModifiers.erase(position);
		}

		return GetValue();
	}
};

class StatString
{
public:
	const char* LongValue;
	const char* ShortValue;

	StatString(const char* _longValue, const char* _shortValue) : LongValue(_longValue), ShortValue(_shortValue) {};
};

enum class AttributeType
{
	Strength,
	Dexterity,
	Constitution,
	Intelligence,
	Wisdom,
	Charisma,
	Luck,
	LENGTH
};

class Attribute : public Stat<AttributeType>
{
public:
	static const std::map<AttributeType, StatString> AllAttributes;
	Attribute() {};
	Attribute(AttributeType attributeType) : Stat(attributeType, 10) {};
};

enum class SkillType
{
	Firearms,
	MeleeWeapons,
	Explosives,
	Unarmed,
	FirstAid,
	Medicine,
	Lockpicking,
	Hacking,
	Repair,
	Mechanics,
	Electrician,
	Science,
	Stealth,
	Pickpocket,
	Survival,
	Botany,
	Barter,
	Deception,
	Persuasion,
	LENGTH
};

class Skill : public Stat<SkillType>
{
public:
	static const std::map<SkillType, StatString> AllSkills;
	Skill() {};
	Skill(SkillType skillType) : Stat(skillType, 0) {};
};