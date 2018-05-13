#include "stdafx.h"
#include "CRational.h"

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	double numerator = m_numerator;
	double denominator = m_denominator;

	return numerator / denominator;
}

void CRational::Normalize()
{
	int gcd;
	int numerator = abs(m_numerator);
	int denominator = m_denominator;

	while (denominator != 0)
	{
		std::swap(numerator, denominator);
		denominator = denominator % numerator;
	}
	gcd = (numerator != 0) ? numerator : 1;

	m_numerator /= gcd;
	m_denominator /= gcd;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+() const
{
	return *this;
}

CRational const operator+(CRational const& firstValue, CRational const& secondValue)
{
	return CRational(firstValue.GetNumerator() * secondValue.GetDenominator() + secondValue.GetNumerator() * firstValue.GetDenominator(), firstValue.GetDenominator() * secondValue.GetDenominator());
}

CRational const operator-(CRational const& firstValue, CRational const& secondValue)
{
	return firstValue + (-secondValue);
}

CRational const operator*(CRational const& firstValue, CRational const& secondValue)
{
	return CRational(firstValue.GetNumerator() * secondValue.GetNumerator(), firstValue.GetDenominator() * secondValue.GetDenominator());
}

CRational const operator/(CRational const& firstValue, CRational const& secondValue)
{
	return CRational(secondValue.GetDenominator(), secondValue.GetNumerator()) * firstValue;
}

CRational& CRational::operator+=(CRational const& value)
{
	*this = *this + value;

	return *this;
}

CRational& CRational::operator-=(CRational const& value)
{
	*this += -value;

	return *this;
}

CRational& CRational::operator*=(CRational const& value)
{
	*this = *this * value;

	return *this;
}

CRational& CRational::operator/=(CRational const& value)
{
	*this = *this / value;

	return *this;
}

bool operator==(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue - secondValue).GetNumerator() == 0;
}

bool operator!=(CRational const& firstValue, CRational const& secondValue)
{
	return !(firstValue == secondValue);
}

bool operator<(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue.GetNumerator() * secondValue.GetDenominator() < secondValue.GetNumerator() * firstValue.GetDenominator());
}

bool operator<=(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue < secondValue) || (firstValue == secondValue);
}

bool operator>(CRational const& firstValue, CRational const& secondValue)
{
	return !(firstValue <= secondValue);
}

bool operator>=(CRational const& firstValue, CRational const& secondValue)
{
	return !(firstValue < secondValue);
}

std::ostream& operator<<(std::ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}

std::istream& operator>>(std::istream& input, CRational& rational)
{
	int numerator;
	int denominator;

	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit);
	}

	return input;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	bool isNumberNegative = false;

	int numerator = m_numerator;
	int denominator = m_denominator;
	int intPart = 0;

	if (numerator < 0)
	{
		isNumberNegative = true;
		numerator = abs(numerator);
	}

	while (numerator >= denominator)
	{
		numerator -= denominator;
		intPart++;
	}

	if (isNumberNegative)
	{
		intPart = -intPart;
		numerator = -numerator;
	}

	CRational rationalPart(numerator, denominator);

	return std::make_pair(intPart, rationalPart);
}
