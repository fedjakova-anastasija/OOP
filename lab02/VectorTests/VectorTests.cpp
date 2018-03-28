#include "stdafx.h"
#include "../vector/Vector.h"

TEST_CASE("Works with empty vector", "[processVector]")
{
	std::vector<double> emptyVector;
	ProcessVector(emptyVector);
	CHECK(emptyVector.empty());
}

TEST_CASE("Works  with a vector consisting of zeros", "[processVector]")
{
	std::vector<double> vector{0, 0, 0, 0, 0};
	std::vector<double> expectedVector{0.0, 0.0, 0.0, 0.0, 0.0};
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}

TEST_CASE("Works with a vector consisting of several elements", "[processVector]")
{
	std::vector<double> vector{8, 2, 5, 4, 16};
	const double ARITHMETIC_MEAN = (8.0 + 2.0 + 5.0 + 4.0 + 16.0) / 5;
	std::vector<double> expectedVector = { 8 + ARITHMETIC_MEAN, 2 + ARITHMETIC_MEAN, 5 + ARITHMETIC_MEAN, 4 + ARITHMETIC_MEAN, 16 + ARITHMETIC_MEAN };
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}

TEST_CASE("Works with a vector consisting of several other elements", "[processVector]")
{
	std::vector<double> vector{-50, 0, 147, 89, 231};
	const double ARITHMETIC_MEAN = (147.0 + 89.0 + 231.0) / 3;
	std::vector<double> expectedVector = { -50 + ARITHMETIC_MEAN, 0 + ARITHMETIC_MEAN, 147 + ARITHMETIC_MEAN, 89 + ARITHMETIC_MEAN, 231 + ARITHMETIC_MEAN };
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}
