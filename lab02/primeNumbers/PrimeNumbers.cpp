#include "stdafx.h"
#include "PrimeNumbers.h"

std::set<int> InsertPrimeNumbersInSet(const std::vector<bool>& numbersCheck);

int StringToLong(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

bool CheckBounds(int upperBound)
{
	if (upperBound < 1)
	{
		std::cout << "The upper bound must be greater than 0." << std::endl;
		return false;
	}

	if (upperBound > UPPER_BOUND)
	{
		std::cout << "The upper bound must not be greater than UPPER_BOUND." << std::endl;
		return false;
	}

	return true;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> numbers(upperBound + 1, true);
	for (size_t i = 2; i * i < numbers.size(); ++i)
	{
		if (numbers[i])
		{
			for (size_t j = i * i; j < numbers.size(); j += i)
			{
				numbers[j] = false;
			}
		}
	}

	return InsertPrimeNumbersInSet(numbers);
}

std::set<int> InsertPrimeNumbersInSet(const std::vector<bool>& numbers)
{
	std::set<int> primeNumbers;
	for (size_t i = 2; i < numbers.size(); ++i)
	{
		if (numbers[i])
		{
			primeNumbers.insert(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

void PrintPrimeNumbers(std::set<int>& primeNumbersSet)
{
	std::copy(primeNumbersSet.begin(), primeNumbersSet.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}