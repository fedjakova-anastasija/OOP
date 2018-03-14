// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const size_t SIZE = 3;

struct Matrix3x3
{
	double items[SIZE][SIZE];
};

struct Matrix2x2
{
	double items[SIZE - 1][SIZE - 1];
};

bool ReadMatrix(std::istream& input, Matrix3x3& matrix)
{
	for (size_t row = 0; row < SIZE; row++)
	{
		for (size_t col = 0; col < SIZE; col++)
		{
			if (!(input >> matrix.items[row][col]))
			{
				return false;
			}
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments." << endl;
		cout << "Usage: invert.exe <input file>" << endl;
		return 1;
	}

	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "File input cannot be opened" << endl;
		return 1;
	}

    return 0;
}

