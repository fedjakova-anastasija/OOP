// dictonary.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Dictionary.h"
#include "windows.h" 

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2)
	{
		std::cout << "Неверное количество аргументов." << std::endl;
		std::cout << "Правильный ввод: dictonary.exe <dictonary file>" << std::endl;
		return 1;
	}

	const std::string inputFile = argv[1];
	Dictionary dictionary;
	if (!ReadDictionary(inputFile, dictionary))
	{
		return 1;
	}

	bool saveChanges = DialogWithUser(dictionary);
	if ((!SaveDictionary(inputFile, dictionary)) || (!saveChanges))
	{
		return 1;	
	}

	return 0;
}

