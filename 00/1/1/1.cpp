// ConsoleApplication1.cpp : Defines the entry point for the console application.
/*Задание 1 – 10 баллов
Напишите программу, которая выводит через запятую все четные числа диапазона от 1 до 100,
отсортированные в порядке убывания, т.е. 100, 98, 96, …, 6, 4, 2 
*/

#include "stdafx.h"

int main()
{
	int i;
	for (i = 100; i >= 1; i -= 2)
	{
		printf("%d", i);
		if (i != 2)
		{
			printf(", ");
		}
	}
	printf("\n");

	return 0;
}

