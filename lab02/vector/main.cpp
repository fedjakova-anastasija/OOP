// vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"

int main()
{
	std::vector<double> vectorOfNumbers;
	ReadVector(vectorOfNumbers);
	ProcessVector(vectorOfNumbers);
	std::sort(vectorOfNumbers.begin(), vectorOfNumbers.end());
	PrintVector(vectorOfNumbers);

	return 0;
}
