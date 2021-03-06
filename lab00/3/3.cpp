// 3.cpp : Defines the entry point for the console application.
/*Задание 3. – 30 баллов
Разработайте программу, выводящую числа Фибоначчи диапазона от 0 до N.
Целочисленный параметр N (верхняя граница) должен быть указан пользователем в виде аргумента командной строки.
Числа последовательности должны выводиться через запятую по 5 чисел в каждой строке.
*/

#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>
#include <string>
#include <iostream>

using namespace std;

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

void PrintFibonacciNumbers(int & prev, int & upperBoundm)
{
	const int MAXINT = 2147483647;

	int curr;
	int number = 1;
	int step = 1;

	cout << prev;
	cout << " ";

	while (number <= upperBound)
	{
		if ((number <= MAXINT) && (number >= 1))
		{
			cout << number;

			curr = prev;
			prev = number;
			number = curr + prev;
			step += 1;

			cout << " ";

			if ((number > upperBound) || (number > MAXINT) || (number < 0))
			{
				number = MAXINT;
			}

			if (step == 5)
			{
				cout << endl;
				step = 0;
			}
		}
	}
	cout << endl;
}

int main(int argc, char *argv[])
{
	int argument = 1;
	int prev = 1;
	bool flag = true;

	if (argc <= 1)
	{
		cout << "The upper limit must not be empty." << endl;
		return 1;
	}

	bool err;
	int upperBound = StringToInt(argv[argument], err);

	if (err)
	{
		cout << "Argument is not a number." << endl;
		return 1;
	}

	if (upperBound < 1)
	{
		cout << "The upper limit must be greater than 0." << endl;
		return 1;
	}

	if (errno == ERANGE)
	{
		cout << "The upper limit must not be greater than MAXINT." << endl;
		return 1;
	}

	PrintFibonacciNumbers(prev, upperBound);

    return 0;
}

