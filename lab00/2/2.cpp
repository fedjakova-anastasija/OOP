// 2.cpp : Defines the entry point for the console application.
/*Задание 2. – 10 баллов
Разработайте программу,  выводящую в порядке возрастания все целые числа диапазона от 1 до N,
делящиеся без остатка на сумму своих цифр.
*/

#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>
#include <string>
#include <iostream>

using namespace std;

// calculates sum of the digits of i
int SumDigits(int i)
{
	int sum = 0;

	// цикл продолжается до тех пор, пока число не станет равным 0
	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

int main(int argc, char *argv[])
{
	const int MAXINT = 2147483647;
	const string SPACE = " ";
	int argument = 1;

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

	for (int i = 1; i <= param; ++i)
	{
		if (i % SumDigits(i) == 0)
		{
			cout << i;
			cout << SPACE;
		}
	}

	cout << endl;

	return 0;
}

