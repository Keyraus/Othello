#include "utils.h"

Board* Board_Init() {
	Board* board = (Board*)calloc(1, sizeof(Board));
	assert(board);

	board->grid[4][4] = WHITE;
	board->grid[4][5] = BLACK;
	board->grid[5][4] = BLACK;
	board->grid[5][5] = WHITE;

	
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

Pawn Board_addPawn(Board* board, int x, int y, Pawn pawn)
{
	int total = 0;
	if (!Board_getCountPlays(board))
	{
		pawn = pawn % 2 + 1;
		Board_checkGain(board, pawn);
		if (!Board_getCountPlays(board))
		{
			return NONE;
		}
	}
	else if (board->gain[x][y])
	{
		x++;
		y++;

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
		pawn = pawn % 2 + 1;
		Board_checkGain(board, pawn);
		if (!Board_getCountPlays(board))
		{
			pawn = pawn % 2 + 1;
			Board_checkGain(board, pawn);
			if (!Board_getCountPlays(board))
			{
				return NONE;
			}
		}
		
	}

	//Board_checkGain(board, pawn);
	return pawn;
}

void Board_setGain(Board* board, int value)
{

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; ++x)
			board->gain[x][y] = value;
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
	Board_setGain(board, 0);
	int ispossible = 0;
	int mem = 0;
	for (int x = 1; x < 9; ++x)
		for (int y = 1; y < 9; y++)
		{
			if (Board_getColor(board, x - 1, y - 1) == NONE)
			{
				for (int i = -1; i < 2; i++)
					for (int j = -1; j < 2; j++)
					{
						if (i == 0 && j == 0)
							continue;

						mem = board->gain[x - 1][y - 1];
						(board->gain[x - 1][y - 1]) += Board_changeGain(board, x + i - 1, y + j - 1, i, j, colorToCheck);
						if ((board->gain[x - 1][y - 1]) > mem)
						{
							(board->gain[x - 1][y - 1])--;
							if ((board->gain[x - 1][y - 1]) > mem)
								ispossible = 1;
						}
					}
			}
		}
	return ispossible;
}

void Board_printGain(Board* board)
{
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; x++)
			printf("%d|", board->gain[x][y]);
		printf("\n");
	}
}

Pawn Board_countPieces(Board* board, int* white, int* black, int* none)
{
	int tab[3] = { 0 };
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; x++)
			tab[Board_getColor(board, x, y)]++;
	}
	*white = tab[WHITE];
	*black = tab[BLACK];
	*none = tab[NONE];
	if (tab[WHITE] > tab[BLACK])
		return WHITE;
	else if (tab[BLACK] > tab[WHITE])
		return BLACK;
	else
		return NONE;
}

int Board_changeGain(Board* board, int x, int y, int x_d, int y_d, Pawn color)
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
		accu = Board_changeGain(board, x + x_d, y + y_d, x_d, y_d, color);
		if (accu)
		{
			return ++accu;
		}
	}
	return 0;
}

int Board_getCountPlays(Board* board)
{
	int count = 0;
	for (int y = 0; y < 8; ++y) 
		for (int x = 0; x < 8; x++)
			if (board->gain[x][y])
				count++;

	return count;
}

void Board_render(Board* board, SDL_Renderer* renderer, SDL_Texture* texture[6], Pawn winnerColor, int pawns[3], int flag) {
	int num = 0;
	
	SDL_Color White = { 255,255,255 };
	SDL_Rect pos = { 0,0,105,105 };
	SDL_Rect numrect = { 0,0,200,225 };
	SDL_Rect numpos = { 0,25,50,50 };
	int numdix = 0;
	int numunit = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++)
			if (Board_getColor(board, x, y)) {
				pos.x = x * 100;
				pos.y = y * 100;
				SDL_RenderCopy(renderer, texture[Board_getColor(board, x, y)], NULL, &pos);
			}
			else if (board->gain[x][y]) {
				num = board->gain[x][y];
				if (num / 10 > 0) {
					numrect.x = numrect.w;
					numrect.y = (num / 6) * numrect.h;
					numpos.x = 25 + 100 * x;
					numpos.y = 25 + 100 * y;
					SDL_RenderCopy(renderer, texture[3], &numrect, &numpos);	
					num -= 10;
				}
				numrect.x = num % 5 * numrect.w;
				numrect.y = (num / 6) * numrect.h;
				numpos.x = 100 * x + 40;
				numpos.y = 100 * y + 25;
				SDL_RenderCopy(renderer, texture[3], &numrect, &numpos);

			}
	}
	if (flag) {
		pos.h = 600;
		pos.w = 700;
		pos.x = 50;
		pos.y = 100;
		SDL_RenderCopy(renderer, texture[5], NULL, &pos);
		pos.h = 200;
		pos.w = 200;
		pos.x = 300;
		pos.y = 275;
		SDL_RenderCopy(renderer, texture[winnerColor], NULL, &pos);
		pos.h = 100;
		pos.w = 100;
		numdix = (pawns[winnerColor] / 10) - 1;
		numunit = pawns[winnerColor] - (numdix + 1) * 10;



		numrect.x = 500 * ( numdix % 6);
		numrect.y = 500 * (numdix / 6);
		numpos.x = 350;
		numpos.y = 375;
		SDL_RenderCopy(renderer, texture[3], &numrect, &numpos);

		numrect.x = numunit % 6 * 500;
		numrect.y = (numunit-1) / 6 * 500;
		numpos.x = 380;
		numpos.y = 375;
		SDL_RenderCopy(renderer, texture[3], &numrect, &numpos);
	}
}