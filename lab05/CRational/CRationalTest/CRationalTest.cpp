#include "stdafx.h"
#include "../CRational/CRational.h"
#include <sstream>

void CheckValue(CRational const& rationalNumber, int expectedNumerator, int expectedDenominator)
{
	REQUIRE(rationalNumber.GetNumerator() == expectedNumerator);
	REQUIRE(rationalNumber.GetDenominator() == expectedDenominator);
}

TEST_CASE("Check CRational", "[CRational]")
{
	SECTION("Rational number with numerator only")
	{
		CheckValue(CRational(10), 10, 1);
		CheckValue(CRational(-10), -10, 1);
	}

	SECTION("Rational number with denominator less than 0")
	{
		CheckValue(CRational(1, -2), -1, 2);
	}
	SECTION("Rational number with denominator is 0")
	{
		CheckValue(CRational(1, 0), 0, 1);
	}
	SECTION("Rational number with denominator more than 0")
	{
		CheckValue(CRational(1, 2), 1, 2);
	}

	SECTION("Returns the ratio of the numerator and denominator as a double number")
	{
		REQUIRE(CRational(3, 2).ToDouble() == 1.5);
		REQUIRE(CRational(0, 2).ToDouble() == 0.0);
		REQUIRE(CRational(1, -3).ToDouble() == static_cast<double>(-1) / static_cast<double>(3));
	}

	SECTION("Unary '+' returns equal number")
	{
		CRational rational(1, 2);
		CheckValue(+rational, 1, 2);
	}

	SECTION("Unary '-' returns number with opposite sign")
	{
		CRational rational(1, 2);
		CheckValue(-rational, -1, 2);
	}

	SECTION("Binary '+' returns the result of addition of")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(1, 4);
			CheckValue(rationalFirst + rationalSecond, 3, 4);
		}

		SECTION("an integer")
		{
			CRational rational(1, 4);
			CheckValue(rational + 1, 5, 4);
		}

		SECTION("an integer")
		{
			CRational rational(1, 4);
			CheckValue(1 + rational, 5, 4);
		}
	}

	SECTION("Binary '-' returns the result of the difference of")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(3, 2);
			CheckValue(rationalFirst - rationalSecond, -1, 1);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(rational - 1, -1, 2);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(1 - rational, 1, 2);
		}
	}

	SECTION("Operator '+=' performs an increase in the rational number by the amount of")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(1, 3);
			CheckValue(rationalFirst += rationalSecond, 5, 6);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(rational += 1, 3, 2);
		}
	}

	SECTION("Operator'-=' performs a reduction in the rational number by the value of")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(1, 6);
			CheckValue(rationalFirst -= rationalSecond, 1, 3);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(rational -= 1, -1, 2);
		}
	}

	SECTION("Operation '*' multiplies the value of the first rational number by")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(2, 3);
			CheckValue(rationalFirst * rationalSecond, 1, 3);
		}

		SECTION("integer")
		{
			CRational rational(1, 2);
			CheckValue(rational * -3, -3, 2);
		}

		SECTION("integer")
		{
			CRational rational(1, 2);
			CheckValue(7 * rational, 7, 2);
		}
	}

	SECTION("Operation '/' returns a quotient of a rational number with")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(2, 3);
			CheckValue(rationalFirst / rationalSecond, 3, 4);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(rational / 3, 1, 6);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(3 / rational, 6, 1);
		}
	}

	SECTION("Operation '*=' multiplies the value of the first rational number by")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(2, 3);
			CheckValue(rationalFirst *= rationalSecond, 1, 3);
		}

		SECTION("an integer")
		{
			CRational rational(3, 2);
			CheckValue(rational *= 4, 6, 1);
		}
	}

	SECTION("Operation '/=' divides the first rational number by")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(2, 3);
			CheckValue(rationalFirst /= rationalSecond, 3, 4);
		}

		SECTION("an integer")
		{
			CRational rational(1, 2);
			CheckValue(rational /= 3, 1, 6);
		}
	}

	SECTION("Operation '==' checks the equality of a rational number with")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(2, 4);

			REQUIRE(rationalFirst == rationalFirst);
			REQUIRE_FALSE(rationalFirst == 1/3);
			REQUIRE(rationalFirst == rationalSecond);
		}

		SECTION("an integer")
		{
			CRational rational(4);

			REQUIRE(4 == rational); 
			REQUIRE_FALSE(1/2 == rational);
			REQUIRE(rational == 4);
			REQUIRE_FALSE(rational == 1 / 2);
		}
	}

	SECTION("Operation '!=' checks the inefficiency of a rational number with")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(4, 9);
			CRational rationalSecond(4, 11);

			REQUIRE(rationalFirst != rationalSecond);
			REQUIRE_FALSE(rationalFirst != rationalFirst);
		}

		SECTION("an integer")
		{
			CRational rational(1);

			REQUIRE(4 != rational);
			REQUIRE_FALSE(rational != rational);
			REQUIRE(rational != 4);
			REQUIRE_FALSE(rational != 9/9);
		}
	}

	SECTION("Operation '<' compares a rational number to")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(1, 2);
			CRational rationalThird(1, 2);

			REQUIRE(rationalFirst < rationalSecond);
			REQUIRE_FALSE(rationalSecond < rationalFirst);
			REQUIRE_FALSE(rationalSecond < rationalThird);
		}

		SECTION("an integer")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(1);

			REQUIRE(rationalFirst < 1);
			REQUIRE_FALSE(1 < rationalFirst);
			REQUIRE_FALSE(1 < rationalSecond);
		}
	}

	SECTION("Operation '<=' compares a rational number to")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(3, 9);
			CRational rationalThird(1, 2);

			REQUIRE(rationalFirst <= rationalSecond);
			REQUIRE(rationalFirst <= rationalThird);
			REQUIRE_FALSE(rationalFirst <= 1/4);
		}

		SECTION("an integer")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(1);

			REQUIRE(rationalFirst <= rationalSecond);
			REQUIRE(1 <= rationalSecond);
			REQUIRE_FALSE(rationalSecond <= rationalFirst);
		}
	}

	SECTION("Operation '>' compares a rational number to")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(1, 2);
			CRational rationalSecond(1, 3);
			CRational rationalThird(1, 2);

			REQUIRE(rationalFirst > rationalSecond);
			REQUIRE_FALSE(rationalSecond > rationalFirst);
			REQUIRE_FALSE(rationalSecond > rationalThird);
		}

		SECTION("an integer")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(1);

			REQUIRE(rationalSecond > rationalFirst);
			REQUIRE_FALSE(rationalFirst > rationalSecond);
			REQUIRE_FALSE(rationalSecond > 1);
		}
	}

	SECTION("Operation '>=' compares a rational number to")
	{
		SECTION("the rational")
		{
			CRational rationalFirst(2, 4);
			CRational rationalSecond(1, 2);

			REQUIRE(rationalFirst >= rationalSecond);
			REQUIRE(rationalFirst >= 1/3);
			REQUIRE_FALSE(1/2 >= rationalFirst);
		}

		SECTION("an integer")
		{
			CRational rationalFirst(1, 3);
			CRational rationalSecond(1);

			REQUIRE(rationalSecond >= rationalFirst);
			REQUIRE(rationalSecond >= 1);
			REQUIRE_FALSE(rationalFirst >= rationalSecond);
		}
	}

	SECTION("Operation '<<' outputs a rational number to the output stream")
	{
		SECTION("positive")
		{
			CRational rational(1, 2);
			std::stringstream  output;
			output << rational;
			REQUIRE(output.str() == "1/2");
		}

		SECTION("negative")
		{
			CRational rational(-1, 2);
			std::stringstream  output;
			output << rational;
			REQUIRE(output.str() == "-1/2");
		}
	}

	SECTION("Operation '>>' enters a rational number in the input stream")
	{
		SECTION("positive")
		{
			CRational rational;
			std::stringstream input("1/2");
			input >> rational;
			CheckValue(rational, 1, 2);
		}

		SECTION("negative")
		{
			CRational rational;
			std::stringstream input("-1/2");
			input >> rational;
			CheckValue(rational, -1, 2);
		}
	}

	SECTION("Returns the representation of a rational number in the form of a mixed fraction")
	{

		SECTION("division whole")
		{
			CRational rational(4, 2);
			std::pair<int, CRational> newRational = rational.ToCompoundFraction();
			REQUIRE(newRational.first == 2);
			REQUIRE(newRational.second == CRational());
		}

		SECTION("positive")
		{
			CRational rational(8, 3);
			std::pair<int, CRational> newRational = rational.ToCompoundFraction();
			REQUIRE(newRational.first == 2);
			REQUIRE(newRational.second == CRational(2, 3));
		}

		SECTION("negative")
		{
			CRational rational(-8, 3);
			std::pair<int, CRational> newRational = rational.ToCompoundFraction();
			REQUIRE(newRational.first == -2);
			REQUIRE(newRational.second == CRational(-2, 3));
		}

		SECTION("positive rational without int part")
		{
			CRational rational(1, 3);
			std::pair<int, CRational> newRational = rational.ToCompoundFraction();
			REQUIRE(newRational.first == 0);
			REQUIRE(newRational.second == CRational(1, 3));
		}

		SECTION("negative rational without int part")
		{
			CRational rational(-1, 3);
			std::pair<int, CRational> newRational = rational.ToCompoundFraction();
			REQUIRE(newRational.first == 0);
			REQUIRE(newRational.second == CRational(-1, 3));
		}
	}
}
