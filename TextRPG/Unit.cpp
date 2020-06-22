#include "Unit.h"

const char* kHeight =		"unit_hg";
const char* kWeight =		"unit_wg";
const char* kName =			"unit_nm";
const char* kStatus =		"unit_st";
const char* kTraits =		"unit_tr";
const char* kInventory =	"unit_inv";

json Unit::SerializeData() const
{
	json data;

	data[kHeight]	= mHeight;
	data[kWeight]	= mWeight;
	data[kName]		= Name;

	data[kInventory] = std::move(UnitInventory.SerializeData());
	data[kStatus]	 = std::move(Status.SerializeData());

	data[kTraits] = json::array();
	for (const auto& trait : Traits)
	{
		data[kTraits].emplace_back(std::move(trait.SerializeData()));
	}

	return data;
}

void Unit::DeserializeData(json data)
{
	if (!data.is_object())
	{
		return;
	}

	if (data.contains(kHeight) && data[kHeight].is_number_integer())
	{
		mHeight = data[kHeight].get<uint8>();
	}

	if (data.contains(kWeight) && data[kWeight].is_number_integer())
	{
		mWeight = data[kWeight].get<uint8>();
	}

	if (data.contains(kName) && data[kName].is_string())
	{
		Name = data[kName].get<std::string>();
	}

	if (data.contains(kInventory))
	{
		Inventory tmpInventory;
		tmpInventory.DeserializeData(data[kInventory]);

		UnitInventory = std::move(tmpInventory);
	}

	if (data.contains(kStatus))
	{
		UnitStatus tmpStatus;
		tmpStatus.DeserializeData(data[kStatus]);

		Status = std::move(tmpStatus);
	}

	if (data.contains(kTraits) && data[kTraits].is_array())
	{
		Traits.clear();
		for (const auto& trait : data[kTraits])
		{
			UnitTraits tmpTrait;
			tmpTrait.DeserializeData(trait);

			Traits.emplace_back(std::move(tmpTrait));
		}
	}
}

Unit::Unit(const uint16& startingAge, const uint8& startingHeight, const uint8& startingWeight)
{
	Unit::Name = "";

	Unit::Status = UnitStatus(startingAge);

	Unit::mHeight = startingHeight;
	Unit::mWeight = startingWeight;
}