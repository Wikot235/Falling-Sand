#include <SDL.h>
#include <iostream>

int w = 1280;
int h = 720;

int mousex;
int mousey;

SDL_Window* window = SDL_CreateWindow("Falling Sand Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

void KillGame()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Rect particle{ w / 2, h / 2, 20, 20 };

	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				KillGame();
				return 0;
			}
		}

		SDL_Delay(1000);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &particle);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

	return 0;
}