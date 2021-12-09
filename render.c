#include "render.h"
#include "game.h"

SDL_Color text_color = { 161, 214, 226 };
TTF_Font* font;

static SDL_Texture* set_score(SDL_Renderer* renderer, int score, char score_char[12], int* score_width, int* score_height)
{
	snprintf(score_char, 12, "%d", score);

	SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_char, text_color);
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

	*score_width = score_surface->w;
	*score_height = score_surface->h;

	SDL_FreeSurface(score_surface);

	return score_texture;
}

void init_font()
{
	font = TTF_OpenFont("Square One.ttf", 100);
}

void update_font(int size)
{
	TTF_CloseFont(font);
	font = TTF_OpenFont("Square One.ttf", size);
}

void render_screen(SDL_Renderer* renderer)
{
	int score1_width;
	int score1_height;

	int score2_width;
	int score2_height;

	char left_score_char[12];
	char right_score_char[12];

	SDL_Rect left_paddle_rect = { (int)player_one_p.x, (int)player_one_p.y, player_width, player_height };
	SDL_Rect right_paddle_rect = { (int)player_two_p.x, (int)player_two_p.y, player_width, player_height };
	SDL_Rect ball_rect = { (int)ball_p.x, (int)ball_p.y, ball_size, ball_size };

	SDL_Texture* score1_texture = set_score(renderer, left_score, left_score_char, &score1_width, &score1_height);
	SDL_Texture* score2_texture = set_score(renderer, right_score, right_score_char, &score2_width, &score2_height);

	SDL_Rect left_score_rect = { (win_width - score1_width) / 2 - 100 , 30, score1_width, score1_height };
	SDL_Rect right_score_rect = { (win_width - score2_width) / 2 + 100, 30, score2_width, score2_height };

	SDL_SetRenderDrawColor(renderer, 0, 59, 79, 255);
	/*SDL_SetRenderDrawColor(renderer, 25, 149, 173, 255);*/
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 102, 165, 173, 255);
	SDL_SetRenderDrawColor(renderer, 161, 214, 226, 255);

	SDL_RenderDrawRect(renderer, &left_paddle_rect);
	SDL_RenderFillRect(renderer, &left_paddle_rect);

	SDL_RenderDrawRect(renderer, &right_paddle_rect);
	SDL_RenderFillRect(renderer, &right_paddle_rect);

	SDL_RenderDrawRect(renderer, &ball_rect);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderCopy(renderer, score1_texture, NULL, &left_score_rect);
	SDL_RenderCopy(renderer, score2_texture, NULL, &right_score_rect);

	SDL_DestroyTexture(score1_texture);
	SDL_DestroyTexture(score2_texture);

	SDL_RenderPresent(renderer);
}