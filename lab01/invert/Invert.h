#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

const size_t MATRIX_SIZE = 3;

struct Matrix3x3
{
	double items[MATRIX_SIZE][MATRIX_SIZE];
};

struct Matrix2x2
{
	double items[MATRIX_SIZE - 1][MATRIX_SIZE - 1];
};

bool ReadMatrix(const std::string& fileIn, Matrix3x3& matrix);
bool InvertMatrix(const Matrix3x3& matrix, Matrix3x3& invertedMatrix);
void PrintMatrix(const Matrix3x3& matrix);