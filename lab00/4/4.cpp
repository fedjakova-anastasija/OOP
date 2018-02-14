// 4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <cerrno>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int StringToInt(const char * str, bool & err)
{
	char * pLastChar = NULL;

	double param = strtol(str, &pLastChar, 10);

	err = ((*str == '\0') || (*pLastChar != '\0'));

	return param;
}

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		cout << "Program calculates sum of its command line arguments.\n";

		return 0;
	}

	double sum = 0;
	char o;

	for (int i = 1; i < argc; ++i)
	{
		bool err;
		cout << "%d", argv[i];
		
		if (*argv[i] == '+')
		{
			o = '+';
		}
		else
		{
			if (*argv[i] == '-')
			{
				o = '-';
			}
			else
			{
				if (*argv[i] == '*')
				{
					o = '*';
				}
				else
				{
					if (*argv[i] == '/')
					{
						o = '/';
					}
					else
					{
						if (i == 1)
						{
							o = '+';
						}

						int param = StringToInt(argv[i], err);

						if (err)
						{
							cout << "Argument #%d is not a number\n.", i;

							return 1;
						}

						if (o == '+')
						{
							sum += param;
						}

						if (o == '-')
						{
							sum -= param;
						}

						if (o == '*')
						{
							sum *= param;
						}

						if (o == '/')
						{
							sum /= param;
						}
					}
				}
			}
		}
	}
	cout << " = %d" << fixed << setprecision(3) << sum << endl;

	return 0;
}

