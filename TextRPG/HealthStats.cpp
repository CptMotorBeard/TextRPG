#include "HealthStats.h"

const char* kAge = "healthStats_age";
const char* kHealth = "healthStats_hlt";
const char* kSanity = "healthStats_snt";
const char* kWeeks = "healthStats_wks";
const char* kAlive = "healthStats_alv";
const char* kInjuries = "healthStats_inj";
const char* kIllness = "healthStats_ill";
const char* kDiseases = "healthStats_dss";

json Injury::SerializeData() const
{
	json data;
	return data;
}

json Illness::SerializeData() const
{
	json data;
	return data;
}

json Disease::SerializeData() const
{
	json data;
	return data;
}

json HealthStats::SerializeData() const
{
	json data;

	data[kAge] = mAge;
	data[kHealth] = mHealth;
	data[kSanity] = mSanity;
	
	data[kWeeks] = mCurrentWeeksAlive;
	data[kAlive] = mAlive;

	data[kInjuries] = json::array();
	for (const auto& injury : mInjuries)
	{
		data[kInjuries].emplace_back(std::move(injury.SerializeData()));
	}

	data[kIllness] = json::array();
	for (const auto& illness : mIllnesses)
	{
		data[kIllness].emplace_back(std::move(illness.SerializeData()));
	}
	
	data[kDiseases] = json::array();
	for (const auto& disease : mDiseases)
	{
		data[kDiseases].emplace_back(std::move(disease.SerializeData()));
	}

	return data;
}

void Injury::DeserializeData(json data) {}

void Illness::DeserializeData(json data) {}

void Disease::DeserializeData(json data) {}

void HealthStats::DeserializeData(json data)
{
	if (!data.is_object())
	{
		return;
	}

	if (data.contains(kAge) && data[kAge].is_number_integer())
	{
		mAge = data[kAge];
	}

	if (data.contains(kHealth) && data[kHealth].is_number_integer())
	{
		mHealth = data[kHealth];
	}

	if (data.contains(kSanity) && data[kSanity].is_number_integer())
	{
		mSanity = data[kSanity];
	}

	if (data.contains(kWeeks) && data[kWeeks].is_number_integer())
	{
		mCurrentWeeksAlive = data[kWeeks];
	}
	
	if (data.contains(kAlive) && data[kAlive].is_boolean())
	{
		mAlive = data[kAlive];
	}

	if(data.contains(kInjuries) && data[kInjuries].is_array())
	{
		mInjuries.clear();
		for (const auto& injury : data[kInjuries])
		{
			Injury tmpInjury;
			tmpInjury.DeserializeData(injury);

			mInjuries.emplace_back(std::move(tmpInjury));
		}
	}	

	if (data.contains(kIllness) && data[kIllness].is_array())
	{
		mIllnesses.clear();
		for (const auto& illness : data[kIllness])
		{
			Illness tmpIllness;
			tmpIllness.DeserializeData(illness);

			mIllnesses.emplace_back(std::move(tmpIllness));
		}
	}
	
	if (data.contains(kDiseases) && data[kDiseases].is_array())
	{
		mDiseases.clear();
		for (const auto& disease : data[kDiseases])
		{
			Disease tmpDisease;
			tmpDisease.DeserializeData(disease);

			mDiseases.emplace_back(std::move(tmpDisease));
		}
	}

	std::random_device dev;
	HealthStats::mUnitRandom = std::mt19937(dev());
}

HealthStats::HealthStats(uint16 startingAge)
{
	mAge = startingAge;

	mHealth = 10;
	mSanity = 10;
	mAlive = true;

	std::random_device dev;
	mUnitRandom = std::mt19937(dev());

	mCurrentWeeksAlive = (uint8)Random::WeeklyDistribution(mUnitRandom);
}