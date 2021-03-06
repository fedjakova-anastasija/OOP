#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include <string>

TEST_CASE("Check FindMax", "[FindMax]")
{
	SECTION("Works with empty vector")
	{
		std::vector<int> emptyVector;
		int maxValue;
		REQUIRE_FALSE(FindMax(emptyVector, maxValue, [](const auto& firstNumber, const auto& secondNumber) {
			return firstNumber < secondNumber;
		}));
	}

	SECTION("Works with one element in vector")
	{
		std::vector<int> arr{ 1 };
		int maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstNumber, const auto& secondNumber) {
			return firstNumber < secondNumber;
		}));
		REQUIRE(maxValue == 1);
	}

	SECTION("Works with the same elements in vector")
	{
		std::vector<int> arr{ 1, 1, 1 };
		int maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstNumber, const auto& secondNumber) {
			return firstNumber < secondNumber;
		}));
		REQUIRE(maxValue == 1);
	}

	SECTION("Return maxValue from a nonempty int vector")
	{
		std::vector<int> arr{ 5, 12, 0 };
		int maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstNumber, const auto& secondNumber) {
			return firstNumber < secondNumber;
		}));
		REQUIRE(maxValue == 12);
	}

	SECTION("Return maxValue from a nonempty float vector")
	{
		std::vector<float> arr{ 5.1f, 12.2f, 0.3f };
		float maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstNumber, const auto& secondNumber) {
			return firstNumber < secondNumber;
		}));
		REQUIRE(maxValue == 12.2f);
	}

	SECTION("Return maxValue from a nonempty string vector")
	{
		std::vector<std::string> arr{ "hello", "word", "hi" };
		std::string maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstString, const auto& secondString) {
			return firstString < secondString;
		}));
		REQUIRE(maxValue == "word");
	}

	SECTION("Return maxValue from a nonempty struct vector")
	{
		struct Athlete
		{
			std::string fullName;
			float height;
			float weight;
		};

		std::vector<Athlete> arr{
			{ "Vanya", 172, 80 },
			{ "Kolya", 180, 76 },
			{ "Dasha", 165, 50 },
		};
		Athlete maxValue;
		REQUIRE(FindMax(arr, maxValue, [](const auto& firstAthlete, const auto& secondAthlete) {
			return firstAthlete.fullName < secondAthlete.fullName;
		}));
		REQUIRE(maxValue.fullName == "Vanya");

		REQUIRE(FindMax(arr, maxValue, [](const auto& firstAthlete, const auto& secondAthlete) {
			return firstAthlete.height < secondAthlete.height;
		}));
		REQUIRE(maxValue.height == 180);

		REQUIRE(FindMax(arr, maxValue, [](const auto& firstAthlete, const auto& secondAthlete) {
			return firstAthlete.weight < secondAthlete.weight;
		}));
		REQUIRE(maxValue.weight == 80);
	}
}
