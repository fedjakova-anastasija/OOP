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
		const double MIN_NUMBER = *min_element(vectorOfNumbers.begin(), vectorOfNumbers.end());
		const double MAX_NUMBER = *max_element(vectorOfNumbers.begin(), vectorOfNumbers.end());

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

		const double ARITHMETIC_MEAN = sum / count;

		for (auto& element : vectorOfNumbers)
		{
			element += ARITHMETIC_MEAN;
		}

		if ((MIN_NUMBER == MAX_NUMBER) && (MIN_NUMBER == 0))
		{
			for (auto& element : vectorOfNumbers)
			{
				element = 0.0;
			}
		}
	}
}

void PrintVector(const std::vector<double>& vectorOfNumbers)
{
	std::cout << std::fixed << std::setprecision(3);
	std::copy(vectorOfNumbers.begin(), vectorOfNumbers.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl;
}
