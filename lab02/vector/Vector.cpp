#include "stdafx.h"
#include "Vector.h"

void ReadVector(std::vector<double>& vectorOfNumbers)
{
	copy(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), back_inserter(vectorOfNumbers));
}

void ProcessVector(std::vector<double>& vectorOfNumbers)
{
	if (!vectorOfNumbers.empty())
	{
		double sum = 0;
		int count = 0;
		for (auto& element : vectorOfNumbers)
		{
			if (element > 0)
			{
				sum += element;
				count++;
			}
		}

		const double ARITHMETIC_MEAN = (count == 0) ? 0 : sum / count;
		
		for (auto& element : vectorOfNumbers)
		{
			element += ARITHMETIC_MEAN;
		}
	}
}

void PrintVector(const std::vector<double>& vectorOfNumbers)
{
	std::cout << std::fixed << std::setprecision(3);
	std::copy(vectorOfNumbers.begin(), vectorOfNumbers.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl;
}
