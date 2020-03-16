#pragma once
#include "BaseIncludes.h"

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

enum class SkillType
{
	Test,
	LENGTH
};

template <typename E>
class Stat
{
	static_assert(std::is_enum<E>::value, "Type E must be an enum");
private:
	E mStatType;
	uint16 mBaseValue;
	std::vector<int8> mModifiers;

public:
	Stat(E statType, uint16 startingValue);

	int16 GetTotalModifier();

	const uint16& GetBaseValue();

	uint16 GetValue();

	uint16 AddModifier(int8 modifier);
};

class Attribute : public Stat<AttributeType>
{
public:
	static const AttributeType AllAttributes[(int)AttributeType::LENGTH];
	static std::string AttributeString(AttributeType type);

	Attribute(AttributeType attributeType) : Stat(attributeType, 10) {};
};

class Skill : public Stat<SkillType>
{
public:
	static const SkillType AllSkills[(int)SkillType::LENGTH];
	static std::string SkillString(SkillType type);

	Skill(SkillType skillType) : Stat(skillType, 0) {};
};