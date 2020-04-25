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
	const std::map<AttributeType, StatString> AllAttributes
	{
		{AttributeType::Strength, StatString("Strength", "STR")},
		{AttributeType::Dexterity, StatString("Dexterity", "DEX")},
		{AttributeType::Constitution, StatString("Constitution", "CON")},
		{AttributeType::Intelligence, StatString("Intelligence", "INT")},
		{AttributeType::Wisdom, StatString("Wisdom", "WIS")},
		{AttributeType::Charisma, StatString("Charisma", "CHA")},
		{AttributeType::Luck, StatString("Luck", "LCK")}
	};

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
	const std::map<SkillType, const char*> AllSkills
	{
		{ SkillType::Firearms, "Firearms" },
		{ SkillType::MeleeWeapons, "Melee Weapons" },
		{ SkillType::Explosives, "Explosives" },
		{ SkillType::Unarmed, "Unarmed" },
		{ SkillType::FirstAid, "First Aid" },
		{ SkillType::Medicine, "Medicine" },
		{ SkillType::Lockpicking, "Lockpicking" },
		{ SkillType::Hacking, "Hacking" },
		{ SkillType::Repair, "Repair" },
		{ SkillType::Mechanics, "Mechanics" },
		{ SkillType::Electrician, "Electrician" },
		{ SkillType::Science, "Science" },
		{ SkillType::Stealth, "Stealth" },
		{ SkillType::Pickpocket, "Pickpocket" },
		{ SkillType::Survival, "Survival" },
		{ SkillType::Botany, "Botany" },
		{ SkillType::Barter, "Barter" },
		{ SkillType::Deception, "Deception" },
		{ SkillType::Persuasion, "Persuasion" }
	};

	Skill(SkillType skillType) : Stat(skillType, 0) {};
};