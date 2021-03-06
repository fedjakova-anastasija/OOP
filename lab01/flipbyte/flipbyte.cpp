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

int StringToInt(const char* str, bool& err);
uint8_t FlipByte(uint8_t number);
bool IsNumberInBounds(int number);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Wrong number of arguments." << endl;
		cout << "Usage: flipbyte.exe <input byte>" << endl;
		return 1;
	}

	bool wasErr;
	int number = StringToInt(argv[1], wasErr);
	if (wasErr)
	{
		cout << "Input is not a number." << endl;
		return 1;
	}

	if (!IsNumberInBounds(number))
	{
		return 1;
	}

	uint8_t byteNumber = static_cast<uint8_t>(number);
	int newNumber = FlipByte(byteNumber);
	cout << newNumber << endl;

	return 0;
}

int StringToInt(const char* str, bool& err)
{
	char * pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

uint8_t FlipByte(uint8_t number)
{
	uint8_t result = 0;

	for (int i = 0; i < CHAR_BIT; i++)
	{
		result <<= 1;
		result |= number & 1;
		number >>= 1;
	}

	return result;
}

bool IsNumberInBounds(int number)
{

	if (number < 0)
	{
		cout << "Input must not be less than zero" << endl;
		return false;
	}
	
	if (number > UINT8_MAX)
	{
		cout << "Input must not be more then 255" << endl;
		return false;
	}

	return true;
}
