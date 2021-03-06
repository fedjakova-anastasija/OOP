#include "stdafx.h"
#include "../vector/Vector.h"

TEST_CASE("Empty vector is converted to an empty vector", "[processVector]")
{
	std::vector<double> emptyVector;
	ProcessVector(emptyVector);
	CHECK(emptyVector.empty());
}

TEST_CASE("The vector of zeros does not change", "[processVector]")
{
	std::vector<double> vector{0, 0, 0, 0, 0};
	std::vector<double> expectedVector{0.0, 0.0, 0.0, 0.0, 0.0};
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}

TEST_CASE("When processing a vector consisting of several elements, the arithmetic mean of the positive numbers of these elements is added to each element", "[processVector]")
{
	std::vector<double> vector{8, 2, 5, 4, 16};
	const double arithmeticMean = (8.0 + 2.0 + 5.0 + 4.0 + 16.0) / 5;
	std::vector<double> expectedVector = { 8 + arithmeticMean, 2 + arithmeticMean, 5 + arithmeticMean, 4 + arithmeticMean, 16 + arithmeticMean };
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}

TEST_CASE("When processing a vector consisting of several other elements, the arithmetic mean of the positive numbers of these elements is added to each element", "[processVector]")
{
	std::vector<double> vector{-50, 0, 147, 89, 231};

	const double arithneticMean = (147.0 + 89.0 + 231.0) / 3;
	std::vector<double> expectedVector = { -50 + arithneticMean, 0 + arithneticMean, 147 + arithneticMean, 89 + arithneticMean, 231 + arithneticMean };
	ProcessVector(vector);
	CHECK(vector == expectedVector);
}
