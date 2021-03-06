// primeNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumbers.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments." << std::endl;
		std::cout << "Usage: PrimeNumbers.exe <upper bound>" << std::endl;
		std::cout << "Upper bound <= " << UPPER_BOUND << std::endl;
		return 1;
	}

	bool err;
	int upperBound = StringToLong(argv[1], err);

	if (err)
	{
		std::cout << "Argument is not a number." << std::endl;
		return 1;
	}

	if (!CheckBounds(upperBound))
	{
		return 1;
	}

	auto primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(primeNumbersSet);

	return 0;
}