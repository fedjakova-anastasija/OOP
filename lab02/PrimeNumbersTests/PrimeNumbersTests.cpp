#include "stdafx.h"
#include "../primeNumbers/PrimeNumbers.h"

bool IsArgumentNumber(bool err)
{
	if (err)
	{
		std::cout << "Argument is not a number." << std::endl;
		return false;
	}
	
	return true;
}

TEST_CASE("Return error if upper bound larger than UPPER_BOUND", "[primeNumbers]")
{
	bool err;
	int upperBound = StringToLong("100000001", err);
	CHECK(!CheckBounds(upperBound));
}

TEST_CASE("Return error if upper bound not a number", "[primeNumbers]")
{
	bool err;
	int upperBound = StringToLong("number", err);
	CHECK(!IsArgumentNumber(err));
}

TEST_CASE("Return error if upper bound less than 1", "[primeNumbers]")
{
	bool err;
	int upperBound = StringToLong("0", err);
	CHECK(!CheckBounds(upperBound));
}

/*TEST_CASE("5761455 prime numbers in the range up to UPPER_BOUND", "[primeNumbers]")
{
	std::set<int> primeNumbersSet;
	primeNumbersSet = GeneratePrimeNumbersSet(UPPER_BOUND);
	CHECK(primeNumbersSet.size() == 5761455);
}*/

TEST_CASE("2, 3, 5, 7, 11, 13, 17, 19 are prime numbers in the range up to 20", "[primeNumbers]")
{
	auto primeNumbersSet = GeneratePrimeNumbersSet(20);
	CHECK(primeNumbersSet == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19 });
}
