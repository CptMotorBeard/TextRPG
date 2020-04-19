#pragma once
#include "BaseIncludes.h"

class Resources
{
public:
	enum class Resource
	{
		BuildingMaterial,
		Money,
		Science
	};

	std::unordered_map<Resource, uint32> MaterialResources;
};