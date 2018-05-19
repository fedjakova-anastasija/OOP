#include "stdafx.h"
#include "CMyString.h"

CMyString::CMyString()
	: CMyString("")
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_pChars = std::make_unique<char[]>(length + 1);
	memcpy(m_pChars.get(), pString, length + 1);
	m_pChars[length] = '\0';
	m_length = length;
}

CMyString::CMyString(CMyString const& other)
{
	if (other.m_length > 0)
	{
		m_pChars = std::make_unique<char[]>(other.m_length + 1);
		memcpy(m_pChars.get(), other.m_pChars.get(), other.m_length + 1);
		m_length = other.m_length;
	}
}

CMyString::CMyString(CMyString&& other)
	: m_pChars(std::move(other.m_pChars))
	, m_length(other.m_length)
{
	other.Clear();
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		std::swap(m_pChars, other.m_pChars);
		std::swap(m_length, other.m_length);
		other.Clear();
	}

	return *this;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pChars ? m_pChars.get() : "";
}

CMyString CMyString::SubString(size_t startPos, size_t length = SIZE_MAX) const
{
	if ((startPos > m_length) || (startPos < 0) || (startPos + length > m_length))
	{
		throw std::out_of_range("Wrong start position or length");
	}

	if (startPos == m_length)
	{
		return "";
	}

	return CMyString(&m_pChars[startPos], length);
}

void CMyString::Clear()
{
	m_length = 0;
	m_pChars.reset();
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		std::swap(m_pChars, tmp.m_pChars);
		std::swap(m_length, tmp.m_length);
	}

	return *this;
}

CMyString const CMyString::operator+(const CMyString& string) const
{
	std::unique_ptr<char[]> tmp;
	tmp  = std::make_unique<char[]>(m_length + string.m_length + 1);

	memcpy(tmp.get(), m_pChars.get(), m_length);
	memcpy(tmp.get() + m_length, string.m_pChars.get(), string.m_length + 1);
	tmp[m_length + string.m_length] = '\0';

	return CMyString(tmp.get(), m_length + string.m_length);
}

CMyString const CMyString::operator+=(const CMyString& string)
{
	return *this = *this + string;
}

bool CMyString::operator==(const CMyString& string) const
{
	return m_length == string.m_length ? memcmp(m_pChars.get(), string.m_pChars.get(), m_length) == 0 : false;
}

bool CMyString::operator!=(const CMyString& string) const
{
	return !(*this == string);
}

bool CMyString::operator<(const CMyString& string) const
{
	return m_length == string.m_length ? memcmp(m_pChars.get(), string.m_pChars.get(), m_length) < 0 : m_length < string.m_length;
}

bool CMyString::operator>(const CMyString& string) const
{
	return m_length == string.m_length ? memcmp(m_pChars.get(), string.m_pChars.get(), m_length) > 0 : m_length > string.m_length;
}

bool CMyString::operator>=(const CMyString& string) const
{
	return !(*this < string);
}

bool CMyString::operator<=(const CMyString& string) const
{
	return !(*this > string);
}

char const& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Wrong index");
	}

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Wrong index");
	}

	return m_pChars[index];
}

CMyString const operator+(const std::string& firstString, const CMyString& secondString)
{
	return CMyString(firstString) + secondString;
}

CMyString const operator+(const char* firstString, const CMyString& secondString)
{
	return CMyString(firstString) + secondString;
}

std::istream& operator>>(std::istream& stream, CMyString& string)
{
	std::string input;
	stream >> input;
	string = input;

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const CMyString& string)
{
	stream << string.GetStringData();

	return stream;
}
