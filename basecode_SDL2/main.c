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
	char** image[3] = {
		"images/board.png",
		"images/black.png",
		"images/white.png"
	};

	SDL_Rect pos;
	SDL_Rect pos2;

	pos2.w = 100;
	pos2.h = 100;
	pos.h = 100;
	pos.w = 100;

	SDL_Event e;
	int quit = 0;

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
	SDL_Surface* laimage;
	for (int i = 0; i < 3; i++) {
		laimage = IMG_Load(image[i]);
		texture[i] = SDL_CreateTextureFromSurface(renderer, laimage);
	}
	SDL_FreeSurface(image);

	SDL_SetRenderDrawColor(renderer, 40, 110, 0, 255);

	int setpion = 0;
	int lastcolor = BLACK;
	Board* board = Board_Init();

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
				SDL_GetMouseState(&pos.x, &pos.y);
				pos.x /= 100;
				pos.y /= 100;

				if (!Board_getColor(board, pos.x, pos.y)) {
					lastcolor = (lastcolor + 1) % 2;
					Board_addPawn(board, pos.x, pos.y, lastcolor);
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
					break;

				case SDLK_DOWN:
					break;

				case SDLK_RIGHT:
					break;

				case SDLK_LEFT:
					break;
				}
				break;

			default:
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture[0], NULL, NULL);
		SDL_GetMouseState(&pos2.x, &pos2.y);
		pos2.x = pos2.x / 100 * 100;
		pos2.y = pos2.y / 100 * 100;
		SDL_RenderCopy(renderer, texture[lastcolor], NULL, &pos2);

		for (int x = 0; x < 8; x++)
			for (int y = 0; y < 8; y++)
				if (Board_getColor(board,x,y)) {
					pos.x = x * 100;
					pos.y = y * 100;
					SDL_RenderCopy(renderer, texture[Board_getColor(board,x,y)], NULL, &pos);
				}
					
				
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

