#pragma once

typedef enum Pawn_e
{
	NONE,
	BLACK,
	WHITE,
}Pawn;

typedef struct Board_s
{
	Pawn grid[10][10];
	int gain[8][8];
}Board;

Board* Board_Init();
int Board_changeLine(Board* board, int x, int y, int x_d, int y_d, Pawn color);
int Board_addPawn(Board* board, int x, int y, Pawn pawn);
int Board_changeColor(Board* board, int x, int y);
Pawn Board_getColor(Board* board, int x, int y);
void Board_setGain(Board* board, int value);
int Board_checkGain(Board* board, Pawn colorToCheck);
void Board_render(Board* board, SDL_Renderer* renderer, SDL_Texture* texture[6], Pawn winnerColor, int pawns[3], int flag);
void Board_printGain(Board* board);
int Board_changeGain(Board* board, int x, int y, int x_d, int y_d, Pawn color);
Pawn Board_countPieces(Board* board, int* white, int* black, int* none);
int Board_getCountPlays(Board* board);
