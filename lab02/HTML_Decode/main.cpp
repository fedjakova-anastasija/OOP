// HTML_Decode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTML_Decode.h"

int main()
{
	if (!DecodeHtmlCharacters(std::cin, std::cout))
	{
		return 1;
	}

	return 0;
}
