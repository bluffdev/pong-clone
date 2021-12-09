#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include <SDL2/SDL.h>

extern v2 player_one_p;
extern v2 player_two_p;
extern v2 ball_p;

extern int left_score;
extern int right_score;

void init_game();
void update_game();
static int left_paddle_collision();
static int right_paddle_collision();
void simulate_game(Uint8* input, float dt);

#endif