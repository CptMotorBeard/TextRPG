#pragma once
#include <unordered_map>
#include <map>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdint.h>
#include <vector>

#define int8  std::int8_t
#define int16 std::int16_t
#define int32 std::int32_t
#define int64 std::int64_t

#define uint8  std::uint8_t
#define uint16 std::uint16_t
#define uint32 std::uint32_t
#define uint64 std::uint64_t

namespace Random
{
	const static std::uniform_int_distribution<uint16> DailyDistribution(0, 23);
	const static std::uniform_int_distribution<uint16> WeeklyDistribution(0, 51);
	const static std::uniform_int_distribution<uint16> YearlyDistribution(0, 364);
	
	const static std::uniform_int_distribution<uint16> D100(1, 100);
	const static std::uniform_int_distribution<uint16> D20(1, 20);
	const static std::uniform_int_distribution<uint16> D12(1, 12);
	const static std::uniform_int_distribution<uint16> D10(1, 10);
	const static std::uniform_int_distribution<uint16> D8(1, 8);
	const static std::uniform_int_distribution<uint16> D6(1, 6);
	const static std::uniform_int_distribution<uint16> D4(1, 4);
	const static std::uniform_int_distribution<uint16> D2(1, 2);
};