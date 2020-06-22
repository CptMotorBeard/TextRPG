#pragma once
#include "BaseIncludes.h"

class Injury
{
public:
	json SerializeData() const;
	void DeserializeData(json data);
};

class Illness
{
public:
	json SerializeData() const;
	void DeserializeData(json data);
};

class Disease
{
public:
	json SerializeData() const;
	void DeserializeData(json data);
};

class HealthStats
{
private:
	uint16 mAge;
	uint16 mHealth;
	uint16 mSanity;

	uint8 mCurrentWeeksAlive;
	bool mAlive;

	std::vector<Injury> mInjuries;
	std::vector<Illness> mIllnesses;
	std::vector<Disease> mDiseases;

	std::mt19937 mUnitRandom;

public:
	HealthStats() : HealthStats(0) {};
	HealthStats(uint16 startingAge);

	json SerializeData() const;
	void DeserializeData(json data);
};