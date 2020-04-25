#include "Stats.h"

const std::map<AttributeType, StatString> Attribute::AllAttributes
{
	{AttributeType::Strength, StatString("Strength", "STR")},
	{AttributeType::Dexterity, StatString("Dexterity", "DEX")},
	{AttributeType::Constitution, StatString("Constitution", "CON")},
	{AttributeType::Intelligence, StatString("Intelligence", "INT")},
	{AttributeType::Wisdom, StatString("Wisdom", "WIS")},
	{AttributeType::Charisma, StatString("Charisma", "CHA")},
	{AttributeType::Luck, StatString("Luck", "LCK")}
};

const std::map<SkillType, const char*> Skill::AllSkills
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