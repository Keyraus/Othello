typedef enum Pawn_e
{
	NONE,
	BLACK,
	WHITE
	
}Pawn;

typedef struct Board_s
{
	Pawn grid[8][8];
	int gain[8][8];
}Board;

int Board_addPawn(Board* board, Pawn pawn);
int Board_changeColor(Board* board, int x, int y);
int Board_checkGain(Board* board);

