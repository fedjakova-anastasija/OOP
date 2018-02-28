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

string ReplaceString(const string& newString, const string& searchString, const string& replaceString);
void Replace(ifstream& fileIn, ofstream& fileOut, const string& searchStr, const string& replaceStr);
bool IsFileOk(ifstream& fileIn, ofstream & fileOut);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Incorrect input of arguments." << endl;
		cout << "Correct input: replace.exe <inputFile> <outputFile> <searchString> <replacementString>" << endl;
		return 1;
	}

	const string search = argv[3];
	const string replace = argv[4];

	ifstream fileInput(argv[1]);
	ofstream fileOutput(argv[2]);

	if (IsFileOk(fileInput, fileOutput))
	{
		Replace(fileInput, fileOutput, search, replace);
	}
	else
	{
		return 1;
	}

	return 0;
}

string ReplaceString(const string& newString, const string& searchString, const string& replaceString)
{
	if (searchString == "")
	{
		return newString;
	}

	if (replaceString == "")
	{
		return newString;
	}

	size_t pos = 0;
	string newStr;

	while (pos != string::npos)
	{
		size_t needPos = newString.find(searchString, pos);
		newStr.append(newString, pos, needPos - pos);

		if (needPos != string::npos)
		{
			newStr.append(replaceString);
			needPos += searchString.length();
		}

		pos = needPos;
	}

	return newStr;
}

void Replace(ifstream& fileIn, ofstream & fileOut, const string & searchStr, const string & replaceStr)
{
	string newString;

	while (getline(fileIn, newString))
	{
		fileOut << ReplaceString(newString, searchStr, replaceStr) << endl;
	}
}

bool IsFileOk(ifstream& fileInput, ofstream & fileOutput)
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