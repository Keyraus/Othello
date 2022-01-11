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

	SDL_Texture* texture[3] = {NULL};
	SDL_Surface* image;

	SDL_Rect spriteRect;
	SDL_Rect spriteRect2;

	spriteRect2.w = 100;
	spriteRect2.h = 100;
	spriteRect.h = 100;
	spriteRect.w = 100;

	SDL_Event e;
	int quit = 0;

	int pos = DOWN;

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
		800, 800, 
		SDL_WINDOW_SHOWN
	);

	if (!window)
	{
		printf("[-] ERROR - Failed to create SDL window (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	image = IMG_Load("images/board.png");
	texture[0] = SDL_CreateTextureFromSurface(renderer, image);
	image = IMG_Load("images/black.png");
	texture[1] = SDL_CreateTextureFromSurface(renderer, image);
	image = IMG_Load("images/white.png");
	texture[2] = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	SDL_SetRenderDrawColor(renderer, 40, 110, 0, 255);

	int setpion = 0;
	int lastcolor = BLACK;
	Board* board = (Board*)calloc(1,sizeof(Board));
	for (int x = 0; x < 8; ++x)
		for (int y = 0; y < 8; ++y)
			Board_addPawn(board,x,y, NONE);
	Board_addPawn(board, 3, 3, BLACK);
	Board_addPawn(board, 3, 4, WHITE);
	Board_addPawn(board, 4, 3, WHITE);
	Board_addPawn(board, 4, 4, BLACK);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;

			case SDL_MOUSEBUTTONDOWN:
				printf("boom\n");
				setpion = 1;
				SDL_GetMouseState(&spriteRect.x, &spriteRect.y);
				spriteRect.x = spriteRect.x / 100;
				spriteRect.y = spriteRect.y / 100;

				if (!board->grid[spriteRect.x][spriteRect.y]) {
					lastcolor = (lastcolor + 1) % 2;
					board->grid[spriteRect.x][spriteRect.y] = last;
				}
					
				else
					printf("deja un pion\n");
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				

				case SDLK_ESCAPE:
					quit = 1;
					break;

				case SDLK_UP:
					pos = UP;
					break;

				case SDLK_DOWN:
					pos = DOWN;
					break;

				case SDLK_RIGHT:
					pos = RIGHT;
					break;

				case SDLK_LEFT:
					pos = LEFT;
					break;
				}
				break;

			default:
				break;
			}
		}


		//printf("%d\n", setpion);
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture[0], NULL, NULL);
		SDL_GetMouseState(&spriteRect2.x, &spriteRect2.y);
		spriteRect2.x = spriteRect2.x / 100 * 100;
		spriteRect2.y = spriteRect2.y / 100 * 100;
		SDL_RenderCopy(renderer, texture[last], NULL, &spriteRect2);

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (board->grid[i][j]) {
					spriteRect.x = i * 100;
					spriteRect.y = j * 100;
					SDL_RenderCopy(renderer, texture[board->grid[i][j]], NULL, &spriteRect);
				}
					
				
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

