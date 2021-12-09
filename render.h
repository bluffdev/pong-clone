#ifndef RENDER_H
#define RENDER_H

#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static SDL_Texture* set_score(SDL_Renderer* renderer, int score, char score_char[12], int* score_width, int* score_height);
void init_font();
void update_font(int size);
void render_screen(SDL_Renderer* renderer);

#endif 