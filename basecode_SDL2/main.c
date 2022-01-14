#include "utils.h"

enum ePosition
{
	DOWN,
	LEFT,
	UP,
	RIGHT,
	NB_POSITION
};

int main(int argc, char** argv)
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* texture[6] = {NULL};
	SDL_Surface* image[6] = {
		IMG_Load("images/board.jpg"),
		IMG_Load("images/black.png"),
		IMG_Load("images/white.jpg"),
		IMG_Load("images/num.png"),
		IMG_Load("images/num.png"),
		IMG_Load("images/winner.png"),
	};

	SDL_Rect pos;
	SDL_Rect pos2;

	SDL_Rect numrect;
	SDL_Rect numpos;

	SDL_Rect background = {
		0,0,
		800,800		
	};

	numrect.w = 500;
	numrect.h = 500;
	numrect.x = 0;
	numrect.y = 0;

	numpos.w = 50;
	numpos.h = 50;
	numpos.x = 0;
	numpos.y = 25;



	pos2.w = 105;
	pos2.h = 105;
	pos.h = 100;
	pos.w = 100;

	SDL_Event e;
	int quit = 0;
	int num = 0;
	int flaaaaaaaaaag = 0;
	int pawns[3] = {0};
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			printf("[-] ERROR - Failed to initialise SDL (%s)\n", SDL_GetError());
			return EXIT_FAILURE;
		}
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("[-] ERROR - Failed to initialise SDL_Image (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow("Ma fenetre SDL",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		1000, 800, 
		SDL_WINDOW_SHOWN
	);

	if (!window)
	{
		printf("[-] ERROR - Failed to create SDL window (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < 6; ++i) {
		texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);
		SDL_FreeSurface(image[i]);
	}
		

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	int lastcolor = BLACK;
	Pawn winnerColor = 0;
	Board* board = Board_Init();
	Board_checkGain(board, lastcolor);
	int theend = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: 
				quit = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				if (Bot_doAFlip(board, WHITE, 5)) {
					flaaaaaaaaaag = 1;
					printf("né nififnit\n");
					winnerColor = Board_countPieces(board, &pawns[WHITE], &pawns[BLACK], &pawns[NONE]);
					pawns[winnerColor] = pawns[winnerColor] + pawns[NONE];
					if (winnerColor != NONE)
						printf("Le gagnant gagne avec : %d points\n", pawns[winnerColor]);
					else
						printf("Egalite\n");
				}
				break;
			case SDL_MOUSEBUTTONDOWN:/*
				SDL_GetMouseState(&pos.x, &pos.y);
				pos.x /= 100;
				pos.y /= 100;
				Board_addPawn(board, pos.x, pos.y, BLACK);*/
				while (!Bot_doAFlip(board, BLACK, 6))
					Bot_doAFlip(board, WHITE, 6);
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				}
				break;

			default:
				break;
			}
		}

		SDL_RenderClear(renderer);

		// background

		SDL_RenderCopy(renderer, texture[0], NULL, &background);
		SDL_GetMouseState(&pos2.x, &pos2.y);
		pos2.x = (pos2.x) / 100 * 100 ;
		pos2.y = (pos2.y)/ 100 * 100 ;
		// pyon ki flot avek la souri
		SDL_RenderCopy(renderer, texture[lastcolor], NULL, &pos2);
		Board_render(board, renderer, texture, winnerColor, pawns,flaaaaaaaaaag);
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

