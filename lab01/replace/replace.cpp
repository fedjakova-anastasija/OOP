// replace.cpp : Defines the entry point for the console application.
/*Разработайте программу replace.exe, выполняющую замену всех вхождений подстроки в текстовом файле на другую строку,
и записывающей результат в выходной файл (отличный от входного). Формат командной строки:
replace.exe <input file> <output file> <search string> <replace string>
*/

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string ReplaceString(const string& subject, const string& searchString, const string& replacementString);
bool Replace(ifstream& fileIn, ofstream& fileOut, const string& searchStr, const string& replacementStr);
bool AreFilesOk(ifstream& fileIn, ofstream& fileOut);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Wrong number of arguments." << endl;
		cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << endl;
		return 1;
	}

	const string search = argv[3];
	const string replace = argv[4];

	ifstream fileInput(argv[1]);
	ofstream fileOutput(argv[2]);
	if (!AreFilesOk(fileInput, fileOutput))
	{
		return 1;
	}

	bool ok = Replace(fileInput, fileOutput, search, replace);
	if (!ok)
	{
		return 1;
	}

	return 0;
}

string ReplaceString(const string& subject, const string& searchString, const string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t startPos = 0;
	string resultString;

	while (startPos != string::npos)
	{
		size_t foundPos = subject.find(searchString, startPos);
		resultString.append(subject, startPos, foundPos - startPos);

		if (foundPos != string::npos)
		{
			resultString.append(replacementString);
			foundPos += searchString.length();
		}

		startPos = foundPos;
	}

	return resultString;
}

bool Replace(ifstream& fileIn, ofstream& fileOut, const string& searchStr, const string& replacementStr)
{
	string newString;

	while (getline(fileIn, newString))
	{
		fileOut << ReplaceString(newString, searchStr, replacementStr) << endl;
	}

	return static_cast<bool>(fileOut);
}

bool AreFilesOk(ifstream& fileInput, ofstream& fileOutput)
{
	if (!fileInput.is_open())
	{
		cout << "File input cannot be opened" << endl;
		return false;
	}

	if (!fileOutput.is_open())
	{
		cout << "File output cannot be opened" << endl;
		return false;
	}

	return true;
}