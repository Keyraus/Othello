#include "utils.h"

Board* Board_Init() {
	Board* board = (Board*)calloc(1, sizeof(Board));

	board->grid[4][4] = BLACK;
	board->grid[4][5] = WHITE;
	board->grid[5][4] = WHITE;
	board->grid[5][5] = BLACK;

	
	Board_setGain(board, 0);

	return board;
}


int Board_changeLine(Board* board, int x, int y, int x_d, int y_d, Pawn color)
{
	int accu = 0;
	if (x > 7 || x < 0 || y > 7 || y < 0)
		return 0;
	Pawn colorBoard = Board_getColor(board, x, y);
	if (colorBoard == NONE)
		return 0;
	if (colorBoard == color)
		return 1;
	else
	{
		accu = Board_changeLine(board, x + x_d, y + y_d, x_d, y_d, color);
		if (accu)
		{
			Board_changeColor(board, x, y);
			return accu + 1;
		}
		return 0;
	}
}

int Board_addPawn(Board* board, int x, int y, Pawn pawn)
{
	x++;
	y++;

	int total = 0;
	
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			if (Board_changeLine(board, x + i - 1, y + j - 1, i, j, pawn) > 1) {
				board->grid[x][y] = pawn;
				++total;
			}
		}
	

	return total;
}

void Board_setGain(Board* board, int value)
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; y++)
			board->gain[x][y] = value;
}

void Board_placePawn(Board* board, int x, int y)
{

}

Pawn Board_getColor(Board* board, int x, int y)
{
	return board->grid[x+1][y+1];
}
int Board_changeColor(Board* board, int x, int y)
{
	x++;
	y++;
//	if (board->grid[x][y])
//		return 1;
	if (board->grid[x][y] == BLACK)
		board->grid[x][y] = WHITE;
	else
		board->grid[x][y] = BLACK;
	
	return 0;
}
int Board_checkGain(Board* board, Pawn colorToCheck)
{
	for (int x = 1; x < 9; ++x)
		for (int y = 1; y < 9; y++)
		{
			if (board->gain[x][y] == colorToCheck)
			{
				char directions = 0b11111111;	//012
				if (y == 1)						//7x3
					directions &= 0b00011111;	//654
				if (y == 8)
					directions &= 0b11110001;
				if (x == 1)
					directions &= 0b01111100;
				if (x == 8)
					directions &= 0b11000111;


				if (directions & 0b10000000)
				{
					int i = 0;
					while (board->grid);
				}
				if (directions & 0b01000000)
				{

				}
				if (directions & 0b00100000)
				{

				}
				if (directions & 0b00010000)
				{

				}
				if (directions & 0b00001000)
				{

				}
				if (directions & 0b00000100)
				{

				}
				if (directions & 0b00000010)
				{

				}
				if (directions & 0b00000001)
				{

				}

				

			}
		}
	return 0;
}