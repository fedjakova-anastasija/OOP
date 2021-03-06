// 5.cpp : Defines the entry point for the console application.
/*Задание 5. – 40 баллов
Разработайте программу, вычисляющую расстояние, которое пролетит тело вдоль горизонтальной оси,
брошенное в вакууме под углом α к горизонту с некоторой начальной скоростью Vo.
Вычисленное расстояние программа должна вывести в стандартный поток вывода.
*/

#include "stdafx.h"
#include <cerrno>
#include <iostream>
#include <cmath>

using namespace std;

const int SIZE = 200;
const double Pi = 3.14159265;
const double acceleration = 9.8;

char v0[SIZE];
char a0[SIZE];

double StringToDouble(const char* str, bool & err)
{
	char* pLastChar = NULL;

	double param = strtod(str, &pLastChar);

	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

double CalculateDistance(double angle, double speed)
{
	double distance = 4 * speed * speed / (acceleration * sin(angle * 2 * Pi / 180));

	return distance;
}

bool nextInput(string & answer, bool & next)
{
	if (answer == "exit")
	{ 
		cout << "Goodbye" << endl;
		next = false;

		return false;
	}

	return true;
}

bool NeedNextInput(string & answer, bool & next)
{
	if (nextInput(answer, next))
	{
		cout << "Enter a0 (or type exit): ";
		cin >> a0;
		answer = a0;

		if (nextInput(answer, next))
		{
			bool err;

			double angle = StringToDouble(a0, err);

			if (err)
			{
				cout << "Argument is not a number." << endl;
				return 1;
			}

			double speed = StringToDouble(v0, err);

			if (err)
			{
				cout << "Argument is not a number." << endl;
				return 1;
			}

			if (errno == ERANGE)
			{
				cout << "The upper limit must not be greater than MAXINT." << endl;

				return 1;
			}

			double Distance = CalculateDistance(angle, speed);

			cout << "Distance is: " << Distance << endl;
		}
	}

	return next;
}

int main()
{
	bool next = true;

	while (next)
	{

		cout << "Enter v0 (or type exit): ";
		cin >> v0;
		string answer = v0;		

		NeedNextInput(answer, next);
	}

    return 0;
}

