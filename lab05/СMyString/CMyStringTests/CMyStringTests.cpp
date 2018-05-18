#include "stdafx.h"
#include "../CMyString/CMyString.h"
#include <sstream>

bool AreStringsEqual(const CMyString& firstString, const char* secondString, size_t length)
{
	if (firstString.GetLength() != length)
	{
		return false;
	}

	for (size_t i = 0; i < length; ++i)
	{
		if (firstString.GetStringData()[i] != secondString[i])
		{
			return false;
		}
	}

	return true;
}

TEST_CASE("Test CMString", "[CMyString]")
{
	SECTION("Zero parameters return primary instance")
	{
		CMyString string;
		REQUIRE(AreStringsEqual(string, "", 0));
	}

	SECTION("Empty string returns its own instance")
	{
		CMyString string("");
		REQUIRE(AreStringsEqual(string, "\0", 0));
	}

	SECTION("A non-empty string returns its own instance")
	{
		CMyString string("Hello");
		REQUIRE(AreStringsEqual(string, "Hello", 5));
		CMyString secondString("Hello\0word");
		REQUIRE(AreStringsEqual(secondString, "Hello\0word", 5));
	}

	SECTION("Empty string with length returns its own instance")
	{
		CMyString firstString("", 0);
		REQUIRE(AreStringsEqual(firstString, "", 0));
		CMyString secondString("\0", 0);
		REQUIRE(AreStringsEqual(secondString, "\0", 0));
	}

	SECTION("A non-empty string with length returns its own instance")
	{
		CMyString firstString("Hello", 5);
		REQUIRE(AreStringsEqual(firstString, "Hello", 5));
		CMyString secondString("Hello\0word", 10);
		REQUIRE(AreStringsEqual(secondString, "Hello\0word", 10));
	}

	SECTION("STL library string returns its own instance")
	{
		std::string str("");
		CMyString firstString(str);
		REQUIRE(AreStringsEqual(firstString, str.c_str(), str.length()));
		str = "Hello";
		CMyString secondString(str);
		REQUIRE(AreStringsEqual(secondString, str.c_str(), str.length()));
	}

	SECTION("CMyString instance returns its own instance using copy constructor")
	{
		CMyString firstString("Hello");
		CMyString secondString(firstString);
		REQUIRE(AreStringsEqual(secondString, firstString.GetStringData(), firstString.GetLength()));
	}

	SECTION("CMyString instance returns its own instance using move constructor")
	{
		CMyString string("Hello");
		CMyString firstString(std::move(string));
		REQUIRE(AreStringsEqual(firstString, "Hello", 5));
	}
}

TEST_CASE("Check GetLength")
{
	SECTION("Return length of string")
	{
		CMyString emptyString("");
		REQUIRE(emptyString.GetLength() == 0);
		CMyString string("Hello");
		REQUIRE(string.GetLength() == 5);
	}
}

TEST_CASE("Check GetStringData")
{
	SECTION("Return pointer to an array of string characters")
	{
		CMyString string("Hello");
		REQUIRE(string.GetStringData()[0] == string[0]);
		REQUIRE(string.GetStringData()[3] == string[3]);
		REQUIRE(string.GetStringData()[5] == '\0');
	}
}

TEST_CASE("Check SubString")
{
	SECTION("Returns a substring from a given position")
	{
		CMyString string("Hello");
		REQUIRE(string.SubString(0, 1) == "H");
		REQUIRE(string.SubString(0, 5) == "Hello");
		REQUIRE(string.SubString(1, 3) == "ell");
		CMyString emptyString("");
		REQUIRE(emptyString.SubString(0, 0) == "");
	}

	SECTION("SubString errors")
	{
		CMyString string("Hello");
		REQUIRE_THROWS_AS(string.SubString(-1, 4), std::out_of_range);
		REQUIRE_THROWS_AS(string.SubString(2, 5), std::out_of_range);
	}
}

TEST_CASE("Check Clear")
{
	SECTION("Return clear string")
	{
		CMyString string("Hello");
		string.Clear();
		REQUIRE(AreStringsEqual(string, "", 0));
	}
}

TEST_CASE("Test methods")
{
	SECTION("Operator =")
	{
		SECTION("Return itself")
		{
			CMyString string("Hello");
			string = string;
			REQUIRE(AreStringsEqual(string, "Hello", 5)); 
		}

		SECTION("changes data of first string to the data of second")
		{
			CMyString string("Hello");
			CMyString newString("Hi");
			string = newString;
			REQUIRE(AreStringsEqual(string, "Hi", 2));
		}
	}

	SECTION("Operator +")
	{
		SECTION("Return result of addition of two instances of class CMyString")
		{
			CMyString string("Hello");
			CMyString newString("Hi");
			CMyString addedString("word");
			CMyString result = string + addedString;
			REQUIRE(result == "Helloword");
		}

		SECTION("Return result of adding instance of class CMyString and class std::string")
		{
			CMyString string("Hello");
			std::string addedString("word");
			CMyString result = string + addedString;
			REQUIRE(result == "Helloword");
		}

		SECTION("Return result of adding instance of class CMyString and const char*")
		{
			CMyString string("Hello");
			CMyString result = string + "word";
			REQUIRE(result == "Helloword");
		}
	}

	SECTION("Operator +=")
	{
		SECTION("Add addedString to string of the class CMyString")
		{
			CMyString string("Hello");
			CMyString addedString("word");
			string += addedString;
			REQUIRE(AreStringsEqual(string, "Helloword", 9));
		}
	}

	SECTION("Operator ==")
	{
		SECTION("Returns true if strings are equal")
		{
			CMyString string("Hello");
			CMyString equalString("Hello"); 
			CMyString notEqualString("Hi");
			REQUIRE(string == equalString);
			REQUIRE_FALSE(string == notEqualString);
		}
	}

	SECTION("Operator !=")
	{
		SECTION("Returns false if they are not equal")
		{
			CMyString string("Hello");
			CMyString equalString("Hello");
			CMyString notEqualString("Hi");
			REQUIRE(string != notEqualString);
			REQUIRE_FALSE(string != equalString);
		}
	}

	SECTION("Operator []")
	{
		SECTION("Read character from string by index")
		{
			CMyString string("Hello");
			auto ch = string[0];
			REQUIRE(ch == 'H');
			ch = string[2];
			REQUIRE(ch == 'l');
		}

		SECTION("Operator [] errors")
		{
			CMyString string("Hello");
			REQUIRE_THROWS_AS(string[6], std::out_of_range);
		}
	}

	SECTION("Operator []")
	{
		SECTION("Write character in string by index")
		{
			CMyString str("Hello");
			auto ch = 'l';
			str[0] = ch;
			REQUIRE(str[0] == 'l');
		}

		SECTION("Operator [] errors")
		{
			CMyString str("Hello");
			auto ch = 'l';
			REQUIRE_THROWS_AS(str[7] = ch, std::out_of_range);
		}
	}

	SECTION("Operator <")
	{
		SECTION("Return true if longString is more than string")
		{
			CMyString string("Hello");
			CMyString longString("Helloword");
			CMyString shortString("Hi");
			REQUIRE(string < longString);
			REQUIRE_FALSE(string < shortString);
		}
	}

	SECTION("Operator >=")
	{
		SECTION("Return true if longString is more or equal than string")
		{
			CMyString string("Hello");
			CMyString longString("Hello");
			CMyString shortString("Hi");
			REQUIRE(longString >= string);
			REQUIRE_FALSE(shortString >= string);
		}
	}

	SECTION("Operator >")
	{
		SECTION("Return true if longString is more than string")
		{
			CMyString string("Hello");
			CMyString longString("Helloword");
			CMyString shortString("Hi");
			REQUIRE(longString > string);
			REQUIRE_FALSE(shortString > string);
		}
	}

	SECTION("Operator <=")
	{
		SECTION("Return true if longString is more or equal than string")
		{
			CMyString string("Hello");
			CMyString longString("Helloword");
			CMyString shortString("Hi");
			REQUIRE(longString >= string);
			REQUIRE_FALSE(shortString >= string);
		}
	}

	SECTION(">>")
	{
		SECTION("Read string from the stream")
		{
			std::stringstream strm("Hello");
			CMyString str;
			strm >> str;
			REQUIRE(AreStringsEqual(str, "Hello", 5));
		}
	}

	SECTION("<<")
	{
		SECTION("Write string into stream")
		{
			CMyString string("Hello");
			std::stringstream strm;
			strm << string;
			REQUIRE(strm.str() == "Hello");
		}
	}
}