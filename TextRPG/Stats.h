#pragma once
#include "BaseIncludes.h"

#define ALL_STAT_MAP(enumType, stringValue, shortValue) { enumType :: stringValue, StatString(#stringValue, #shortValue)}

template <typename E>
class Stat
{
	static_assert(std::is_enum<E>::value, "Type E must be an enum");
private:
	const char* kStatType = "stats_sty";
	const char* kBaseValue = "stats_bsv";
	const char* kMod = "stats_mod";

	E mStatType;
	uint16 mBaseValue;
	std::vector<int8> mModifiers;

public:
	Stat() {};
	Stat(const E& statType, const uint16& startingValue)
	{
		mStatType = statType;
		mBaseValue = startingValue;
	};

	json SerializeData() const
	{
		json data;

		data[kStatType] = (int)mStatType;
		data[kBaseValue] = mBaseValue;

		data[kMod] = json::array();
		for (const auto& mod : mModifiers)
		{
			data[kMod].emplace_back(mod);
		}

		return data;
	};

	void DeserializeData(json data)
	{
		if (!data.is_object())
		{
			return;
		}

		if (data.contains(kStatType) && data[kStatType].is_number_integer())
		{
			try
			{
				int index = std::stoi(data[kStatType].get<std::string>());
				mStatType = (E)index;
			}
			catch (const std::exception& e)
			{

			}
		}

		if (data.contains(kBaseValue) && data[kBaseValue].is_number_integer())
		{
			mBaseValue = data[kBaseValue];
		}

		if (data.contains(kMod) && data[kMod].is_array())
		{
			mModifiers.clear();
			for (const auto& mod : data[kMod])
			{
				mModifiers.push_back(mod);
			}
		}
	};

	int16 GetTotalModifier() const
	{
		int16 total = 0;
		for (auto const &attributeModifier : Stat::mModifiers)
		{
			total += attributeModifier;
		}

		return total;
	};

	const uint16& GetBaseValue() const
	{
		return mBaseValue;
	};

	uint16 GetValue() const
	{
		int16 modifier = GetTotalModifier();
		return mBaseValue + modifier;
	};

	uint16 AddModifier(const int8& modifier)
	{
		mModifiers.push_back(modifier);
		return GetValue();
	};

	uint16 RemoveModifier(const int8& modifier)
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