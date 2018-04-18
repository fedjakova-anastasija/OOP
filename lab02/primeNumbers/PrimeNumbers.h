#pragma once
#include "stdafx.h"

const int UPPER_BOUND = static_cast<int>(1E+8);

std::set<int> GeneratePrimeNumbersSet(int upperBound);
int StringToLong(const char * str, bool & err);
bool CheckBounds(int upperBound);
void PrintPrimeNumbers(std::set<int>& primeNumbersSet);