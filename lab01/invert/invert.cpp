#include "stdafx.h"
#include "Invert.h"

bool ReadMatrix(const std::string& fileIn, Matrix3x3& matrix)
{
	std::ifstream inputFile(fileIn);
	if (!inputFile.is_open())
	{
		std::cout << "Input file cannot be opened." << std::endl;
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

void GetInvertedMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix, double determinant)
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

bool InvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix)
{
	double determinant = GetDeterminant(matrix);

	if (determinant == 0)
	{
		return false;
	}

	GetInvertedMatrix(matrix, invertedMatrix, determinant);

	return true;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	std::cout << std::fixed << std::setprecision(3);
	for (size_t row = 0; row < MATRIX_SIZE; ++row)
	{
		for (size_t col = 0; col < MATRIX_SIZE; ++col)
		{
			std::cout << matrix.items[row][col] << " ";
		}
		std::cout << std::endl;
	}
}