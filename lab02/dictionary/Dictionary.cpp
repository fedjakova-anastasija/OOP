#include "stdafx.h"
#include "Dictionary.h"

bool ReadDictionary(const std::string& fileIn, Dictionary& dictionary);
bool SaveDictionary(const std::string& fileOut, const Dictionary& dictionary);
void NewLine(std::string& userAnswer);
bool DialogWithUser(Dictionary& dictionary);
bool GetTranslationByUser(const std::string& unknownWord, std::string& userTranslation);
void NewTranslationByUser(Dictionary& dictionary, const std::string& userAnswer);
bool SaveChangesInDictionary();

bool ReadDictionary(const std::string& fileIn, Dictionary& dictionary)
{
	std::ifstream inputFile(fileIn);
	if (!inputFile.is_open())
	{
		std::cout << "���������� ������� ������� ����" << std::endl;
		return false;
	}

	std::string newWord;
	std::string translation;
	std::pair<std::string, std::string> newPair;
	while (getline(inputFile, newWord))
	{
		std::transform(newWord.begin(), newWord.end(), newWord.begin(), tolower);
		getline(inputFile, translation);
		std::transform(translation.begin(), translation.end(), translation.begin(), tolower);
		newPair = std::make_pair(newWord, translation);
		dictionary.insert(newPair);
	}

	return true;
}

bool SaveDictionary(const std::string& fileOut, const Dictionary& dictionary)
{
	std::ofstream outputFile(fileOut);
	if (!outputFile.is_open())
	{
		std::cout << "���������� ������� �������� ����" << std::endl;
		return false;
	}

	for (const auto& savedTranslation : dictionary)
	{
		outputFile << savedTranslation.first << std::endl
				   << savedTranslation.second << std::endl;
	}

	std::cout << "�� ��������." << std::endl;

	return true;
}

bool DialogWithUser(Dictionary& dictionary)
{
	bool newTranslation = false;
	std::string userAnswer;
	NewLine(userAnswer);
	while (userAnswer != "...")
	{
		if (!FindTranslation(dictionary, userAnswer))
		{
			NewTranslationByUser(dictionary, userAnswer);
			newTranslation = true;
		}

		NewLine(userAnswer);
	}

	return newTranslation ? SaveChangesInDictionary() : false;
}

void NewLine(std::string& userAnswer)
{
	std::cout << R"(������� �����, ������� �������� ������ ��������, ��� "..." ��� ������ �� ������� � ����������)" << std::endl;
	std::getline(std::cin, userAnswer);
	std::transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), tolower);
}

bool FindTranslation(const Dictionary& dictionary, const std::string& userAnswer)
{
	bool foundTranslation = false;
	for (const auto& newPair : dictionary)
	{
		if (newPair.first == userAnswer)
		{
			std::cout << newPair.second << std::endl;
			foundTranslation = true;
		}

		if (newPair.second == userAnswer)
		{
			std::cout << newPair.first << std::endl;
			foundTranslation = true;
		}
	}

	return foundTranslation;
}

bool GetTranslationByUser(const std::string& unknownWord, std::string& userTranslation)
{
	std::cout << R"(����������� ����� ")" << unknownWord << R"(". ������� ������� ��� ������ ������ ��� ������.)" << std::endl;
	getline(std::cin, userTranslation);

	return CheckEmptyAnswer(unknownWord, userTranslation);
}

bool CheckEmptyAnswer(const std::string& unknownWord, std::string& userTranslation)
{
	if (userTranslation.empty())
	{
		std::cout << R"(����� ")" << unknownWord << R"(" ���������������.)" << std::endl;
		return false;
	}

	return true;
}

void NewTranslationByUser(Dictionary& dictionary, const std::string& userAnswer)
{
	std::string translation;
	if (GetTranslationByUser(userAnswer, translation))
	{
		InsertInDictionary(dictionary, userAnswer, translation);
	}
}

void InsertInDictionary(Dictionary& dictionary, const std::string& userAnswer, const std::string& translation)
{
	std::pair<std::string, std::string> newPair;
	newPair = std::make_pair(userAnswer, translation);
	dictionary.insert(newPair);
	std::cout << R"(����� ")" << userAnswer << R"(" ��������� � ������� ��� ")" << translation << R"(".)" << std::endl;
}

bool SaveChangesInDictionary()
{
	std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
	std::string userAnswer;
	getline(std::cin, userAnswer);
	if ((userAnswer == "Y") || (userAnswer == "y"))
	{
		std::cout << "��������� ���������." << std::endl;
		return true;
	}

	return false;
}
