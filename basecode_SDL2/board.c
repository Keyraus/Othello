#include "board.h"

int Board_addPawn(Board* board, int x, int y, Pawn pawn)
{
	if (board->grid[x][y])
		return 1;
	board->grid[x][y] = pawn;
	return 0;
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
	return 0;
}