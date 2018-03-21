// invert.cpp : Defines the entry point for the console application.
/*Разработайте приложение invert.exe, выполняющее инвертирование матрицы 3*3, т.е. 
нахождение обратной матрицы  и выводящее коэффициенты результирующей матрицы в стандартный поток вывода. 
Формат командной строки приложения: invert.exe <matrix file1>
*/

#include "stdafx.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const size_t MATRIX_SIZE = 3;

struct Matrix3x3
{
	double items[MATRIX_SIZE][MATRIX_SIZE];
};

struct Matrix2x2
{
	double items[MATRIX_SIZE - 1][MATRIX_SIZE - 1];
};

bool ReadMatrix(const string& fileIn, Matrix3x3& matrix);
bool IsInputFileOk(ifstream& inputFile);
bool InvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix);
double GetDeterminant(const Matrix3x3& matrix);
void GetInvertedMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix, double determinant);
double GetMinor(const Matrix3x3& matrix, int col, int row);
void PrintMatrix(const Matrix3x3& matrix);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments." << endl;
		cout << "Usage: invert.exe <input file>" << endl;
		return 1;
	}

	Matrix3x3 matrix;
	const string inputFile = argv[1];
	if (!ReadMatrix(inputFile, matrix))
	{
		cout << "Error reading matrix." << endl;
		return 1;
	}

	Matrix3x3 invertedMatrix;
	if (!InvertMatrix(matrix, invertedMatrix))
	{
		cout << "The determinant must be different from zero." << endl;
		return 1;
	}

	PrintMatrix(invertedMatrix);

	return 0;
}

bool ReadMatrix(const string& fileIn, Matrix3x3& matrix)
{
	ifstream inputFile(fileIn);
	if (!IsInputFileOk(inputFile))
	{
		return false;
	}

	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t col = 0; col < MATRIX_SIZE; ++col)
		{
			if (!(inputFile >> matrix.items[row][col]))
			{
				return false;
			}
		}
	}

	return true;
}

bool IsInputFileOk(ifstream& inputFile)
{
	if (!inputFile.is_open())
	{
		cout << "Input file cannot be opened." << endl;
		return false;
	}

	return true;
}

bool InvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix)
{
	const double determinant = GetDeterminant(matrix);

	if (determinant == 0)
	{
		return false;
	}

	GetInvertedMatrix(matrix, invertedMatrix, determinant);

	return true;
}

double GetDeterminant(const Matrix3x3& matrix)
{
	double determinant = matrix.items[0][0] * matrix.items[1][1] * matrix.items[2][2]
		+ matrix.items[1][0] * matrix.items[2][1] * matrix.items[0][2]
		+ matrix.items[2][0] * matrix.items[0][1] * matrix.items[1][2]
		- matrix.items[2][0] * matrix.items[1][1] * matrix.items[0][2]
		- matrix.items[0][0] * matrix.items[2][1] * matrix.items[1][2]
		- matrix.items[1][0] * matrix.items[0][1] * matrix.items[2][2];

	return determinant;
}

void GetInvertedMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix, const double determinant)
{
	int sign = 1;
	for (int row = 0; row < MATRIX_SIZE; ++row)
	{
		for (int col = 0; col < MATRIX_SIZE; ++col)
		{
			double minor = GetMinor(matrix, row, col);
			invertedMatrix.items[row][col] = sign * minor / determinant;
			sign *= -1;
		}
	}
}

double GetMinor(const Matrix3x3& matrix, int col, int row)
{
	Matrix2x2 minorMatrix;
	for (int currRow = 0; currRow < MATRIX_SIZE; currRow++)
	{
		if (currRow == row)
		{
			continue;
		}

		int minorMatrixRow = (currRow > row) ? (currRow - 1) : currRow;

		for (int currCol = 0; currCol < MATRIX_SIZE; currCol++)
		{
			if (currCol == col)
			{
				continue;
			}

			int minorMatrixCol = (currCol > col) ? (currCol - 1) : currCol;

			minorMatrix.items[minorMatrixRow][minorMatrixCol] = matrix.items[currRow][currCol];
		}
	}

	return minorMatrix.items[0][0] * minorMatrix.items[1][1]
		- minorMatrix.items[1][0] * minorMatrix.items[0][1];
}

void PrintMatrix(const Matrix3x3& matrix)
{
	cout << fixed << setprecision(3);
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t col = 0; col < MATRIX_SIZE; ++col)
		{
			cout << matrix.items[row][col] << " ";
		}
		cout << endl;
	}
}
