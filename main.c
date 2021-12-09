#define SDL_MAIN_HANDLED
#include "render.h"
#include "game.h"
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>

int win_width = 1600;
int win_height = 900;

int player_width = 30;
int player_height = 160;

int ball_size = 20;

int running = true;

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, win_width, win_height, SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		printf("Could not create window: %s\n", SDL_GetError());
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer)
	{
		printf("Could not create window: %s\n", SDL_GetError());
	}

	const Uint8* input = SDL_GetKeyboardState(NULL);

	Uint64 frame_start;
	Uint64 frame_end;
	float delta_time = 0;

	srand(time(0));

	float scale = 0.001f;

	init_game();
	init_font();

	while (running)
	{
		// Timing
		frame_start = SDL_GetPerformanceCounter();

		// Input
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					running = false;
					break;

				case SDL_WINDOWEVENT:

					if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						SDL_GetWindowSize(window, &win_width, &win_height);

						player_width = 30 * win_height * scale;
						player_height = 160 * win_height * scale;

						ball_size = 20 * win_height * scale;

						update_font(100 * win_height * scale);

						update_game();
					}
					break;
			}
		}

		// Game Logic
		simulate_game(input, delta_time);

		// Render
		render_screen(renderer);

		frame_end = SDL_GetPerformanceCounter();
		delta_time = (frame_end - frame_start) / (float)SDL_GetPerformanceFrequency();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;
}