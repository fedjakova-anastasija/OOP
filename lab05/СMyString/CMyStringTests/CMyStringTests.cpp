#include "stdafx.h"
#include "../CMyString/CMyString.h"
#include <sstream>

bool AreStringsEqual(const CMyString& stringFirst, const char* stringSecond, size_t length)
{
	if (stringFirst.GetLength() != length)
	{
		return false;
	}

	for (size_t i = 0; i < length; ++i)
	{
		if (stringFirst.GetStringData()[i] != stringSecond[i])
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
	}

	SECTION("Empty string with length returns its own instance")
	{
		CMyString string("", 0);
		REQUIRE(AreStringsEqual(string, "", 0));
	}

	SECTION("A non-empty string with length returns its own instance")
	{
		CMyString string("Hello", 5);
		REQUIRE(AreStringsEqual(string, "Hello", 5));
	}

	SECTION("STL library string returns its own instance")
	{
		std::string str("");
		CMyString stringFirst(str);
		REQUIRE(AreStringsEqual(stringFirst, str.c_str(), str.length()));
		str = "Hello";
		CMyString stringSecond(str);
		REQUIRE(AreStringsEqual(stringSecond, str.c_str(), str.length()));
	}

	SECTION("CMyString instance returns its own instance using copy constructor")
	{
		CMyString stringFirst("Hello");
		CMyString stringSecond(stringFirst);
		REQUIRE(AreStringsEqual(stringSecond, stringFirst.GetStringData(), stringFirst.GetLength()));
	}

	SECTION("CMyString instance returns its own instance using move constructor")
	{
		CMyString string("Hello");
		CMyString string1(std::move(string));
		REQUIRE(AreStringsEqual(string1, "Hello", 5));
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
		try
		{
			CMyString str = string.SubString(-1, 4);
		}
		catch (std::invalid_argument const& error)
		{
			CHECK_THROWS_AS(static_cast<const std::string&>("Wrong start position or length") == error.what());
		}

		try
		{
			CMyString str = string.SubString(2, 5);
		}
		catch (std::invalid_argument const& error)
		{
			REQUIRE(static_cast<const std::string&>("Wrong start position or length") == error.what());
		}
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

struct CMyStringFixture
{
	size_t stringLength = 5;
	CMyString string;
	CMyStringFixture()
		: string("Hello", stringLength)
	{
	}
};

TEST_CASE_METHOD(CMyStringFixture, "overloaded operator")
{
	SECTION("Operator =")
	{
		SECTION("Return itself")
		{
			string = string;
			REQUIRE(AreStringsEqual(string, "Hello", stringLength));
		}

		SECTION("changes data of first string to the data of second")
		{
			CMyString newString("Hi");
			string = newString;
			REQUIRE(AreStringsEqual(string, "Hi", 2));
		}
	}

	SECTION("Operator +")
	{
		SECTION("Return result of addition of two instances of class CMyString")
		{
			string = "Hello";
			CMyString addedString("word");
			CMyString result = string + addedString;
			REQUIRE(result == "Helloword");
		}

		SECTION("Return result of adding instance of class CMyString and class std::string")
		{
			std::string addedString("word");
			CMyString result = string + addedString;
			REQUIRE(result == "Helloword");
		}

		SECTION("Return result of adding instance of class CMyString and const char*")
		{
			CMyString result = string + "word";
			REQUIRE(result == "Helloword");
		}
	}

	SECTION("Operator +=")
	{
		SECTION("Add addedString to string of the class CMyString")
		{
			CMyString addedString("word");
			string += addedString;
			REQUIRE(AreStringsEqual(string, "Helloword", 9));
		}
	}

	SECTION("Operator ==")
	{
		SECTION("Returns true if strings are equal")
		{
			CMyString equalString("Hello");
			REQUIRE(string == equalString);
		}
	}

	SECTION("Operator !=")
	{
		SECTION("Returns false if they are not equal")
		{
			CMyString notEqualString("Hi");
			REQUIRE_FALSE(string == notEqualString);
		}
	}

	SECTION("Operator []")
	{
		SECTION("Read character from string by index")
		{
			auto ch = string[0];
			REQUIRE(ch == 'H');
			ch = string[2];
			REQUIRE(ch == 'l');
		}

		SECTION("Operator [] errors")
		{
			try
			{
				auto ch = string[-1];
			}
			catch (std::invalid_argument const& error)
			{
				REQUIRE(static_cast<const std::string&>("Wrong index") == error.what());
			}

			try
			{
				auto ch = string[6];
			}
			catch (std::invalid_argument const& error)
			{
				REQUIRE(static_cast<const std::string&>("Wrong index") == error.what());
			}
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
			try
			{
				str[-1] = ch;
			}
			catch (std::invalid_argument const& error)
			{
				REQUIRE(static_cast<const std::string&>("Wrong index") == error.what());
			}

			try
			{
				str[7] = ch;
			}
			catch (std::invalid_argument const& error)
			{
				REQUIRE(static_cast<const std::string&>("Wrong index") == error.what());
			}
		}
	}

	SECTION("Operator <")
	{
		SECTION("Return true if longString is more than string")
		{
			CMyString longString("Helloword");
			REQUIRE(string < longString);
		}
	}

	SECTION("Operator >=")
	{
		SECTION("Return true if longString is more or equal than string")
		{
			CMyString longString("Hello");
			REQUIRE(longString >= string);
		}
	}

	SECTION("Operator >")
	{
		SECTION("Return true if longString is more than string")
		{
			CMyString longString("Helloword");
			REQUIRE(longString > string);
		}
	}

	SECTION("Operator <=")
	{
		SECTION("Return true if longString is more or equal than string")
		{
			CMyString longString("Helloword");
			REQUIRE(longString >= string);
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
			std::stringstream strm;
			strm << string;
			REQUIRE(strm.str() == "Hello");
		}
	}
}