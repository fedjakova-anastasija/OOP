// 4.cpp : Defines the entry point for the console application.
/*Задание 4. - 60 баллов.
разработайте программу eval.exe, вычисляющую результат вычисления арифметического выражения,
операции и операнды которого передаются через аргументы командной строки.
Вычисление выражения должно осуществляться без учета приоритета операторов,
результат выводится с точностью до 3 знаков после запятой.*/

#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

double StringToDouble(const char* str, bool & err)
{
	char* pLastChar = NULL;

	double param = strtod(str, &pLastChar);

	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Program calculates sum of its command line arguments." << endl;

		return 0;
	}

	double sum = 0;
	char sign = '!';
	const int MAXINT = 2147483647;


	for (int i = 1; i < argc; ++i)
	{
		bool err;
		cout << *argv[i] << endl;

		if ((*argv[i] != '+') && (*argv[i] != '-') && (*argv[i] != '*') && (*argv[i] != '/'))
		{
			if (i == 1)
			{
				sign = '+';
			}

			double param = StringToDouble(argv[i], err);

			if ((sign == '/') && (param == 0))
			{
				cout << "Division by zero is forbidden" << endl;

				return 1;
			}

			if (err)
			{
				cout << "Argument " << i << " is not a number." << endl;

				return 1;
			}

			if (errno == ERANGE)
			{
				cout << "The upper limit must not be greater than MAXINT." << endl;

				return 1;
			}

			cout << sum << " " << sign << " " <<param << endl;

			switch (sign)
			{
			case '+':
				sum += param;
				break;
			case '-':
				sum -= param;
				break;
			case '*':
				sum *= param;
				break;
			case '/':
				sum /= param;
				break;
			}


		}
		switch (*argv[i])
		{
		case '+':
			sign = '+';
			break;
		case '-':
			sign = '-';
			break;
		case '*':
			sign = '*';
			break;
		case '/':
			sign = '/';
			break;
		}
	}
	cout << " = " << fixed << setprecision(3) << sum << endl;

	return 0;
}

