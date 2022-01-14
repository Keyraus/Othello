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
	TTF_Init();
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* texture[9]= {NULL};
	SDL_Surface* image[9] = {
		IMG_Load("images/board.jpg"),
		IMG_Load("images/black.png"),
		IMG_Load("images/white.png"),
		IMG_Load("images/num.png"),
		IMG_Load("images/num.png"),
		IMG_Load("images/winner.png"),
		IMG_Load("images/jcj.png"),
		IMG_Load("images/jvia.png"),
		IMG_Load("images/o.png")

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
		1100, 800, 
		SDL_WINDOW_SHOWN
	);

	if (!window)
	{
		printf("[-] ERROR - Failed to create SDL window (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	for (int i = 0; i < 9; ++i) {
		texture[i] = SDL_CreateTextureFromSurface(renderer, image[i]);
		SDL_FreeSurface(image[i]);
	}

	TTF_Font* Sans = TTF_OpenFont("data/font.ttf", 10);

	SDL_Color White = { 255,255,255};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "coucou", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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

				if (Bot_doAFlip(board, WHITE, 1)) {
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
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&pos.x, &pos.y);
				pos.x /= 100;
				pos.y /= 100;
				Board_addPawn(board, pos.x, pos.y, BLACK);
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;
				case SDLK_SPACE:
					//Bot_doAFlip(board, BLACK, 1);
					
					break;
				}
				break;

			default:
				break;
			}
		}

		SDL_RenderClear(renderer);

		// background
		background.x = 0;
		background.y = 0;
		background.w = 800;
		background.h = 800;
		SDL_RenderCopy(renderer, texture[0], NULL, &background);
		//SDL_RenderCopy(renderer, Message, NULL, NULL);
		
		SDL_GetMouseState(&pos2.x, &pos2.y);
		pos2.x = (pos2.x) / 100 * 100 ;
		pos2.y = (pos2.y)/ 100 * 100 ;
		// pyon ki flot avek la souri
		if (pos2.x < 800) {
			SDL_SetTextureBlendMode(texture[lastcolor], SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture[lastcolor], 100);
			SDL_RenderCopy(renderer, texture[lastcolor], NULL, &pos2);
			SDL_SetTextureAlphaMod(texture[lastcolor], 255);
		}
		background.x = 800;
		background.y = 0;
		background.w = 300;
		background.h = 100;
		SDL_RenderCopy(renderer, texture[8], NULL, &background);

		background.y = 100;

		SDL_SetTextureBlendMode(texture[6], SDL_BLENDMODE_BLEND);
		
		if (pos2.y == 100 && pos2.x > 800)
			SDL_SetTextureAlphaMod(texture[6], 255);
		else
			SDL_SetTextureAlphaMod(texture[6], 100);
		SDL_RenderCopy(renderer, texture[6], NULL, &background);
		background.y = 200;
		
		SDL_SetTextureBlendMode(texture[7], SDL_BLENDMODE_BLEND);
		
		if (pos2.y == 200 && pos2.x > 700)
			SDL_SetTextureAlphaMod(texture[7], 255);
		else
			SDL_SetTextureAlphaMod(texture[7], 100);
		SDL_RenderCopy(renderer, texture[7], NULL, &background);

		Board_render(board, renderer, texture, winnerColor, pawns,flaaaaaaaaaag);
		
		SDL_RenderPresent(renderer);
	}
	free(board);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

