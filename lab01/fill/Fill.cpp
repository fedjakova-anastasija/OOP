#include "stdafx.h"
#include "Fill.h"


namespace
{
	const int SIZE_WITH_BOARDS = 102;
	const char EMPTY = ' ';
	const char FILLED = '.';
	const char BEGIN = 'O';
	const char BORDER = '#';
	const char INSERT = '-';

	struct Position
	{
		int row;
		int col;
	};

	struct Field
	{
		char cells[SIZE_WITH_BOARDS][SIZE_WITH_BOARDS];
	};
}

void ReadField(std::istream& input, Field& field);
void PrintField(std::ostream& output, const Field& field);
void Fill(Field& field);

const int DIRECTION_COUNT = 4;
const Position OFFSETS[DIRECTION_COUNT] = {
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 0, -1 },
};

void ReadField(std::istream& input, Field& field)
{
	int row = 0;
	while (!input.eof() && row < SIZE_WITH_BOARDS - 2)
	{
		std::string line;
		std::getline(input, line);
		for (size_t col = 0; col < line.length(); ++col)
		{
			field.cells[row + 1][col + 1] = line[col];
		}
		row++;
	}
}

void Fill(Field& field)
{
	std::queue<Position> queue;

	for (int row = 0; row < SIZE_WITH_BOARDS; ++row)
	{
		for (int col = 0; col < SIZE_WITH_BOARDS; ++col)
		{
			if (field.cells[row][col] == BEGIN)
			{
				queue.push({ row, col });
			}
		}
	}

	while (!queue.empty())
	{
		Position position = queue.front();
		queue.pop();

		char currPosition = field.cells[position.row][position.col];

		if (currPosition == INSERT)
		{
			currPosition = FILLED;
		}

		for (int direction = 0; direction < DIRECTION_COUNT; ++direction)
		{
			Position newPosition = position;
			newPosition.row += OFFSETS[direction].row;
			newPosition.col += OFFSETS[direction].col;
			if (field.cells[newPosition.row][newPosition.col] == EMPTY)
			{
				queue.push(newPosition);
				field.cells[newPosition.row][newPosition.col] = INSERT;
			}
		}
	}
}

void PrintField(std::ostream& output, const Field& field)
{
	int maxRow = 0;
	int maxCol = 0;
	for (int row = 1; row < SIZE_WITH_BOARDS - 1; ++row)
	{
		for (int col = 1; col < SIZE_WITH_BOARDS - 1; ++col)
		{
			if (field.cells[row][col] != EMPTY)
			{
				maxRow = std::max(maxRow, row);
				maxCol = std::max(maxCol, col);
			}
		}
	}

	Position size = { maxRow, maxCol };

	for (int row = 1; row <= size.row; ++row)
	{
		for (int col = 1; col <= size.col; ++col)
		{
			output << field.cells[row][col];
		}
		output << std::endl;
	}
}

void Fill(std::istream& input, std::ostream& output)
{
	Field field;

	for (int row = 0; row < SIZE_WITH_BOARDS; ++row)
	{
		for (int col = 0; col < SIZE_WITH_BOARDS; ++col)
		{
			if (row == 0 || row == SIZE_WITH_BOARDS - 1 || col == 0 || col == SIZE_WITH_BOARDS - 1)
			{
				field.cells[row][col] = BORDER;
			}
			else
			{
				field.cells[row][col] = EMPTY;
			}
		}
	}

	ReadField(input, field);
	Fill(field);
	PrintField(output, field);
}
