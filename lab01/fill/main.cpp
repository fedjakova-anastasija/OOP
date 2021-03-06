// fill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fill.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Wrong number of arguments." << std::endl;
		std::cout << "Usage: fill.exe <input file> <output file>" << std::endl;
		return 1;
	}

	const std::string inputFileName = argv[1];
	const std::string outputFileName = argv[2];

	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Input file cannot be opened." << std::endl;
		return 1;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		std::cerr << "Output file cannot be opened." << std::endl;
		return 1;
	}

	Fill(inputFile, outputFile);

	return 0;
}