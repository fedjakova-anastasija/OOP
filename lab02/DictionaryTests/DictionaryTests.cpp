#include "stdafx.h"
#include "../Dictionary/Dictionary.h"

TEST_CASE("Translation of a new word is added to the dictionary", "[Dictionary]")
{
	Dictionary rightDictionary = { { "cat", "кошка" } };
	Dictionary verifiableDictionary;
	InsertInDictionary(verifiableDictionary, "cat", "кошка");
	CHECK(verifiableDictionary == rightDictionary);
}

TEST_CASE("Translation of a new word from English into Russian is searched in the dictionary", "[Dictionary]")
{
	Dictionary dictionary = { { "cat", "кошка" } };
	bool foundTranslation = FindTranslation(dictionary, "cat");
	CHECK(foundTranslation);
}

TEST_CASE("Translation of a new word from Russian into English is searched in the dictionary", "[Dictionary]")
{
	Dictionary dictionary = { { "cat", "кошка" } };
	bool foundTranslation = FindTranslation(dictionary, "кошка");
	CHECK(foundTranslation);
}

TEST_CASE("All translations of words in the dictionary are displayed correctly", "[Dictionary]")
{
	Dictionary dictionary = { { "cat", "кошка" }, { "cat", "кот" } };
	std::string userAnswer = "cat";
	std::string result = "";
	std::string rightResult = "кошка кот ";
	bool foundTranslation = FindTranslation(dictionary, userAnswer);
	for (const auto& newPair : dictionary)
	{
		if (newPair.first == userAnswer)
		{
			result += newPair.second;
			result += " ";
		}
	}
	CHECK(foundTranslation);
	CHECK(result == rightResult);
}

TEST_CASE("Translation of a new word with a different case is searched in the dictionary correctly", "[Dictionary]")
{
	Dictionary dictionary = { { "cat", "кошка" } };
	std::string userAnswer = "cAt";
	std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), tolower);
	bool foundTranslation = FindTranslation(dictionary, userAnswer);
	CHECK(foundTranslation);
}

TEST_CASE("Translation of the new phrase is searched in the dictionary correctly", "[Dictionary]")
{
	Dictionary dictionary = { { "Красная Площадь", "Red Square" } };
	bool foundTranslation = FindTranslation(dictionary, "Красная Площадь");
	CHECK(foundTranslation);
}

TEST_CASE("The dictionary will not change its content after the user refuses to add the translation of a new word", "[Dictionary]")
{
	Dictionary rightDictionary;
	Dictionary verifiableDictionary;
	std::string translation;
	translation = "";
	if (CheckEmptyAnswer("cat", translation))
	{
		InsertInDictionary(verifiableDictionary, "cat", "");
	}
	CHECK(verifiableDictionary == rightDictionary);
}
