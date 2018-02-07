// 2.cpp : Defines the entry point for the console application.
/*Задание 2. – 10 баллов
Разработайте программу,  выводящую в порядке возрастания все целые числа диапазона от 1 до 1000,
делящиеся без остатка на сумму своих цифр.
*/

#include "stdafx.h"

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

int main()
{
	for (int i = 1; i <= 1000; ++i)
	{
		if (i % SumDigits(i) == 0)
		{
			printf("%d", i);
			printf(" ");
		}
	}

	printf("\n");

	return 0;
}

