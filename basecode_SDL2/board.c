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
	return 0;
}
int Board_checkGain(Board* board)
{
	return 0;
}