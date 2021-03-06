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
bool Replace(const string& fileIn, const string& fileOut, const string& searchStr, const string& replacementStr);
bool AreFilesOk(ifstream& fileIn, ofstream& fileOut);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Wrong number of arguments." << endl;
		cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << endl;
		return 1;
	}

	const string fileInput = argv[1];
	const string fileOutput = argv[2];
	const string search = argv[3];
	const string replace = argv[4];

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

bool Replace(const string& fileIn, const string& fileOut, const string& searchStr, const string& replacementStr)
{
	ifstream inputFile(fileIn);
	ofstream outputFile(fileOut);

	if (!AreFilesOk(inputFile, outputFile))
	{
		return 1;
	}

	string newString;
	while (getline(inputFile, newString))
	{
		outputFile << ReplaceString(newString, searchStr, replacementStr) << endl;
	}

	return static_cast<bool>(outputFile);
}

bool AreFilesOk(ifstream& inputFile, ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		cout << "Input file cannot be opened" << endl;
		return false;
	}

	if (!outputFile.is_open())
	{
		cout << "Output file cannot be opened" << endl;
		return false;
	}

	return true;
}