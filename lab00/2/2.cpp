// 2.cpp : Defines the entry point for the console application.
/*Задание 2. – 10 баллов
Разработайте программу,  выводящую в порядке возрастания все целые числа диапазона от 1 до N,
делящиеся без остатка на сумму своих цифр.
*/

#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>

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
	int p = 1;

	if (argc <= 1)
	{
		printf("The upper limit must not be empty.\n");
		return 1;
	}

	bool err;
	int param = StringToInt(argv[p], err);
	
	if (err)
	{
		printf("Argument #%d is not a number\n.", p);
		return 1;
	}

	if (param < 1)
	{
		printf("The upper limit must be greater than 0.\n");
		return 1;
	}

	if (errno == ERANGE)
	{
		printf("The upper limit must not be greater than MAXINT.\n");
		return 1;
	}

	for (int i = 1; i <= param; ++i)
	{
		if ((i % SumDigits(i) == 0) && (i <= MAXINT))
		{
			printf("%d", i);
			printf(" ");
		}
	}

	printf("\n");

	return 0;
}

