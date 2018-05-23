#pragma once
#include <memory>
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString& operator=(CMyString&& other);
	CMyString(const std::string& stlString);

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t startPos, size_t length) const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString const operator+(const CMyString& string) const;
	CMyString const operator+=(const CMyString& string);

	bool operator==(const CMyString& string) const;
	bool operator!=(const CMyString& string) const;
	bool operator<(const CMyString& string) const;
	bool operator>(const CMyString& string) const;
	bool operator>=(const CMyString& string) const;
	bool operator<=(const CMyString& string) const;

	char const& operator[](size_t index) const;
	char& operator[](size_t index);

private:
	using Chars = std::unique_ptr<char[]>; 
	Chars m_pChars = nullptr;
	size_t m_length = 0;
};

CMyString const operator+(const std::string& stringFirst, const CMyString& stringSecond);
CMyString const operator+(const char* stringFirst, const CMyString& stringSecond);

std::istream& operator>>(std::istream& stream, CMyString& string);
std::ostream& operator<<(std::ostream& stream, const CMyString& string);