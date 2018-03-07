// flipbyte.cpp : Defines the entry point for the console application.
/*Разработайте приложение flipbyte.exe, выполняющее изменение порядка следования двоичных
битов в 8-битовом целом числе (байте), заданном в десятичном представлении, на противоположный.
Для этого используйте операторы для работы с битами. «Перевернутый» байт выводится в output также
в десятичном представлении с завершающим символом перевода строки \n. Формат командной строки приложения:
flipbyte.exe <входной байт>
*/

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int StringToInt(const char * str, bool & err);
uint8_t FlipByte(uint8_t number);
bool AreBoundsOk(int number);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect input of arguments." << endl;
		cout << "Correct input: flipbyte.exe <input byte>" << endl;
		return 1;
	}

	bool err;
	int number = StringToInt(argv[1], err);

	if (err)
	{
		cout << "Input is not a number." << endl;
		return 1;
	}

	uint8_t byteNumber = static_cast<uint8_t>(number);

	if (!AreBoundsOk(number))
	{
		return 1;
	}

	int newNumber = FlipByte(byteNumber);
	cout << newNumber << endl;

	return 0;
}

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

uint8_t FlipByte(uint8_t number)
{
	uint8_t result = 0;

	for (int i = 0; i < 8; i++)
	{
		result = result << 1;
		result |= number & 1;
		number = number >> 1;
	}
	return result;
}

bool AreBoundsOk(int number)
{
	const int UPPER_BOUND = 255;
	const int BOTTOM_BOUND = 0;

	if (number < BOTTOM_BOUND)
	{
		cout << "Input must not be less than zero" << endl;
		return false;
	}
	else if (number > UPPER_BOUND)
		{
			cout << "Input must not be more then 255" << endl;
			return false;
		}

	return true;
}
