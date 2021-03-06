#include "stdafx.h"
#include "FindMaxEx.h"

struct Athlete
{
	std::string fullName;
	float height;
	float weight;
};

std::vector<Athlete> athletes{
	{ "Vanya", 172, 80 },
	{ "Kolya", 180, 76 },
	{ "Dasha", 165, 50 },
	{ "Masha", 150, 48 },
	{ "Petya", 169, 76 }
};

int main()
{
	Athlete maxScoreAthlete;
	if (FindMax(athletes, maxScoreAthlete, [](const auto& firstAthlete, const auto& secondAthlete) {
		return firstAthlete.height < secondAthlete.height;
	}))
	{
		std::cout << "Athlete with max height: " << maxScoreAthlete.fullName << " " << maxScoreAthlete.height << " " << maxScoreAthlete.weight << std::endl;
	}
	if (FindMax(athletes, maxScoreAthlete, [](const auto& firstAthlete, const auto& secondAthlete) {
		return firstAthlete.weight < secondAthlete.weight;
	}))
	{
		std::cout << "Athlete with max weight: " << maxScoreAthlete.fullName << " " << maxScoreAthlete.height << " " << maxScoreAthlete.weight << std::endl;
	}

	return 0;
}
