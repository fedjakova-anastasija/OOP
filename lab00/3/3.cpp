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

int main(int argc, char *argv[])
{
	const string SPACE = " ";
	const int MAXINT = 2147483647;
	int curr;
	int prev = 1;
	int number = 1;
	int step = 1;
	int argument = 1;
	bool flag = true;

	if (argc <= 1)
	{
		cout << "The upper limit must not be empty." << endl;
		return 1;
	}

	bool err;
	int param = StringToInt(argv[argument], err);

	if (err)
	{
		cout << "Argument is not a number." << endl;
		return 1;
	}

	if (param < 1)
	{
		cout << "The upper limit must be greater than 0." << endl;
		return 1;
	}

	if (errno == ERANGE)
	{
		cout << "The upper limit must not be greater than MAXINT." << endl;
		return 1;
	}

	cout << prev;
	cout << SPACE;

	while (number <= param)
	{
		if ((number <= MAXINT) && (number >= 1))
		{
			cout << number;

			curr = prev;
			prev = number;
			number = curr + prev;
			step += 1;

			cout << SPACE;

			if ((number > param) || (number > MAXINT) || (number < 0))
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

    return 0;
}

