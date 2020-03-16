#include "HealthStats.h"

HealthStats::HealthStats(uint16 startingAge)
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