typedef enum Pawn_e
{
	BLACK,
	WHITE,
	NONE
}Pawn;

typedef struct Board_s
{
	Pawn grid[8][8];
}Board;

int Board_addPawn(Board* board, Pawn pawn);