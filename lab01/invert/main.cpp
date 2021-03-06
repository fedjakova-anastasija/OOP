// invert.cpp : Defines the entry point for the console application.
/*Разработайте приложение invert.exe, выполняющее инвертирование матрицы 3*3, т.е. 
нахождение обратной матрицы  и выводящее коэффициенты результирующей матрицы в стандартный поток вывода. 
Формат командной строки приложения: invert.exe <matrix file1>
*/

#include "stdafx.h"
#include "Invert.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Wrong number of arguments." << std::endl;
		std::cout << "Usage: invert.exe <input file>" << std::endl;
		return 1;
	}

	Matrix3x3 matrix;
	const std::string inputFile = argv[1];
	if (!ReadMatrix(inputFile, matrix))
	{
		std::cout << "Error reading matrix." << std::endl;
		return 1;
	}

	Matrix3x3 invertedMatrix;
	if (!InvertMatrix(matrix, invertedMatrix))
	{
		std::cout << "The determinant must be different from zero." << std::endl;
		return 1;
	}

	PrintMatrix(invertedMatrix);

	return 0;
}
