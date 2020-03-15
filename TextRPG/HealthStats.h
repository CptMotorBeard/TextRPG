#pragma once
#include "BaseIncludes.h"

class Injury
{

};

class Illness
{

};

class Disease
{

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
	HealthStats(uint16 startingAge)
	{
		mAge = startingAge;

		mHealth = 10;
		mSanity = 10;
		mAlive = true;

		mInjuries = std::vector<Injury>();
		mIllnesses = std::vector<Illness>();
		mDiseases = std::vector<Disease>();

		std::random_device dev;
		mUnitRandom = std::mt19937(dev());

		mCurrentWeeksAlive = Random::WeeklyDistribution(mUnitRandom);
	}

	~HealthStats() {};
};