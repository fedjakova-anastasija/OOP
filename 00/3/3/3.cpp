// 3.cpp : Defines the entry point for the console application.
/*Задание 3. – 30 баллов
Разработайте программу, выводящую числа Фибоначчи  диапазона от 0 до N.
Целочисленный параметр N (верхняя граница) должен быть указан пользователем в виде аргумента командной строки.
Числа последовательности должны выводиться через запятую по 5 чисел в каждой строке.
*/

#include "stdafx.h"
#include "stdlib.h"

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}


int main(int argc, char *argv[])
{
	int j = 0;
	int k = 1;
	int i = 1;
	int t = 1;
	int p = 1;

	if (argc <= 1)
	{
		printf("The upper limit must be greater than 0.\n");
		return 0;
	}
	bool err;
	int param = StringToInt(argv[p], err);

	printf("%d", k);
	printf(" ");

	while (i != param)
	{
		if (i <= 2147483647)
		{	
			j = k;
			k = i;
			i = j + k;			
			t += 1;
			printf("%d", i);
			printf(" ");

			if (err)
			{
				printf("Argument #%d is not a number\n.", i);
				return 1;
			}

			if (t == 5)
			{
				printf("\n");
				t = 0;
			}
		}
	}

    return 0;
}

