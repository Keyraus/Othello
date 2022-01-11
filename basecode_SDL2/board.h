typedef enum Pawn_e
{
	NONE,
	BLACK,
	WHITE,
}Pawn;

typedef struct Board_s
{
	Pawn grid[8][8];
	Pawn gain[8][8]
}Board;

int Board_addPawn(Board* board, int x, int y, Pawn pawn);
int Board_changeColor(Board* board, int x, int y);
Pawn Board_getColor(Board* board, int x, int y);
int Board_checkGain(Board* board, Pawn colorToCheck);