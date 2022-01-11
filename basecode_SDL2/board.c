#include "board.h"

int Board_addPawn(Board* board, int x, int y, Pawn pawn)
{
	if (board->grid[x][y])
		return 1;
	board->grid[x][y] = pawn;
	return 0;
}
Pawn Board_getColor(Board* board, int x, int y)
{
	return board->grid[x][y];
}
int Board_changeColor(Board* board, int x, int y)
{
	if (board->grid[x][y])
		return 1;
	if (board->grid[x][y] == BLACK)
		board->grid[x][y] = WHITE;
	else
		board->grid[x][y] = BLACK;
	
	return 0;
}
int Board_checkGain(Board* board, Pawn colorToCheck)
{
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; y++)
			board->gain[x][y] = 0;
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; y++)
		{
			if (board->gain[x][y] == colorToCheck)
			{
				char directions = 0b11111111;				//012
				if (y == 0)									//7x3
					directions = directions & 0b00011111;	//654
				if (y == 7)
					directions = directions & 0b11110001;
				if (x == 0)
					directions = directions & 0b01111100;
				if (x == 7)
					directions = directions & 0b11000111;


				

			}
		}
	return 0;
}