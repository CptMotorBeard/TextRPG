#include "HealthStats.h"

HealthStats::HealthStats(uint16 startingAge)
{
	HealthStats::mAge = startingAge;

	HealthStats::mHealth = 10;
	HealthStats::mSanity = 10;
	HealthStats::mAlive = true;

	std::random_device dev;
	HealthStats::mUnitRandom = std::mt19937(dev());

	HealthStats::mCurrentWeeksAlive = (uint8)Random::WeeklyDistribution(mUnitRandom);
}