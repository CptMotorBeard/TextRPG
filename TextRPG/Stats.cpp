#include "Stats.h"

const std::map<AttributeType, StatString> Attribute::AllAttributes
{
	ALL_STAT_MAP(AttributeType, Strength, STR),
	ALL_STAT_MAP(AttributeType, Dexterity, DEX),
	ALL_STAT_MAP(AttributeType, Constitution, CON),
	ALL_STAT_MAP(AttributeType, Intelligence, INT),
	ALL_STAT_MAP(AttributeType, Wisdom, WIS),
	ALL_STAT_MAP(AttributeType, Charisma, CHA),
	ALL_STAT_MAP(AttributeType, Luck, LCK)
};

const std::map<SkillType, StatString> Skill::AllSkills
{
	ALL_STAT_MAP(SkillType, Firearms, Firearms),
	ALL_STAT_MAP(SkillType, MeleeWeapons, Melee Weapons),
	ALL_STAT_MAP(SkillType, Explosives, Explosives),
	ALL_STAT_MAP(SkillType, Unarmed, Unarmed),
	ALL_STAT_MAP(SkillType, FirstAid, First Aid),
	ALL_STAT_MAP(SkillType, Medicine, Medicine),
	ALL_STAT_MAP(SkillType, Lockpicking, Lockpicking),
	ALL_STAT_MAP(SkillType, Hacking, Hacking),
	ALL_STAT_MAP(SkillType, Repair, Repair),
	ALL_STAT_MAP(SkillType, Mechanics, Mechanics),
	ALL_STAT_MAP(SkillType, Electrician, Electrician),
	ALL_STAT_MAP(SkillType, Science, Science),
	ALL_STAT_MAP(SkillType, Stealth, Stealth),
	ALL_STAT_MAP(SkillType, Pickpocket, Pickpocket),
	ALL_STAT_MAP(SkillType, Survival, Survival),
	ALL_STAT_MAP(SkillType, Botany, Botany),
	ALL_STAT_MAP(SkillType, Barter, Barter),
	ALL_STAT_MAP(SkillType, Deception, Deception),
	ALL_STAT_MAP(SkillType, Persuasion, Persuasion)
};