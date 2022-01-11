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

	SDL_Texture* texture;
	SDL_Surface* image;
	SDL_Rect spriteRect;
	SDL_Rect spriteRect2;

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

	window = SDL_CreateWindow("Ma fenetre SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("[-] ERROR - Failed to create SDL window (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	image = IMG_Load("data/sprite.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	SDL_SetRenderDrawColor(renderer, 40, 110, 0, 255);

	int setpion = 0;
	int board[8][8] = { 0 };


	positionRect.w = 64;
	positionRect.h = 48;
	positionRect.x = 288;
	positionRect.y = 216;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;

			case SDL_BUTTON_LEFT:
				setpion = 1;


			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = 1;
					break;

				case SDLK_UP:
					pos = UP;
					positionRect.y -= positionRect.h/2;
					break;

				case SDLK_DOWN:
					pos = DOWN;
					positionRect.y += positionRect.h/2;
					break;

				case SDLK_RIGHT:
					pos = RIGHT;
					positionRect.x += positionRect.w / 2;
					break;

				case SDLK_LEFT:
					pos = LEFT;
					positionRect.x -= positionRect.w / 2;
					break;
				}
				break;

			default:
				break;
			}
		}


		printf("%d\n", setpion);
		setpion = 0;
		
		SDL_GetMouseState(&spriteRect2.x, &spriteRect2.y);
		spriteRect2.x = spriteRect2.x / 100 * 100;
		spriteRect2.y = spriteRect2.y / 100 * 100;

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture[0], NULL, NULL);
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j])
					SDL_RenderCopy(renderer, texture[board[i][j]], NULL, &spriteRect);
			}
		}
		
		SDL_RenderCopy(renderer, texture[2], NULL, &spriteRect2);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

