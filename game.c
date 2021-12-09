#include "game.h"

v2 player_one_p;
v2 player_two_p;
v2 ball_p;

int left_score;
int right_score;

v2 ball_dp = { 1100, 0 };

float player_one_dp = 0.f;
float player_two_dp = 0.f;

void init_game()
{
	player_one_p = (v2){ 0, (win_height - player_height) / 2 };
	player_two_p = (v2){ win_width - player_width, (win_height - player_height) / 2 };
	ball_p = (v2){ (win_width - ball_size) / 2, win_height / 2 };

	left_score = 0;
	right_score = 0;
}

void update_game()
{
	player_one_p = (v2){ 0, (win_height - player_height) / 2 };
	player_two_p = (v2){ win_width - player_width, (win_height - player_height) / 2 };
	ball_p = (v2){ (win_width - ball_size) / 2, win_height / 2 };
}

static int left_paddle_collision()
{
	return ball_p.x < player_one_p.x + player_width && (ball_p.y + ball_size > player_one_p.y && ball_p.y < player_one_p.y + player_height && ball_p.x > 0);
}

static int right_paddle_collision()
{
	return ball_p.x + ball_size >= player_two_p.x && (ball_p.y + ball_size > player_two_p.y && ball_p.y < player_two_p.y + player_height && ball_p.x + ball_size < win_width);
}

void simulate_game(Uint8* input, float dt)
{
	float player_one_ddp = 0.f;
	float player_two_ddp = 0.f;

	if (input[SDL_SCANCODE_W] && !input[SDL_SCANCODE_S])
		player_one_ddp -= 3500;

	else if (!input[SDL_SCANCODE_W] && input[SDL_SCANCODE_S])
		player_one_ddp += 3500;

	if (input[SDL_SCANCODE_UP] && !input[SDL_SCANCODE_DOWN])
		player_two_ddp -= 3500;

	else if (!input[SDL_SCANCODE_UP] && input[SDL_SCANCODE_DOWN])
		player_two_ddp += 3500;

	player_one_ddp -= player_one_dp * 4.f;
	player_two_ddp -= player_two_dp * 4.f;

	player_one_p.y = player_one_p.y + (player_one_dp * (dt)) + (player_one_ddp * (dt) * (dt) * .5f);
	player_one_dp = player_one_dp + (player_one_ddp * dt);

	player_two_p.y = player_two_p.y + (player_two_dp * (dt)) + (player_two_ddp * (dt) * (dt)) * .5f;
	player_two_dp = player_two_dp + (player_two_ddp * dt);

	if (player_one_p.y < 0)
	{
		player_one_p.y = 0;
		player_one_dp = 0;
	}

	else if (player_one_p.y + player_height > win_height)
	{
		player_one_p.y = win_height - player_height;
		player_one_dp = 0;
	}

	if (player_two_p.y < 0)
	{
		player_two_p.y = 0;
		player_two_dp = 0;
	}

	else if (player_two_p.y + player_height > win_height)
	{
		player_two_p.y = win_height - player_height;
		player_two_dp = 0;
	}

	ball_p.x += ball_dp.x * (dt);
	ball_p.y += ball_dp.y * (dt);

	if (ball_p.y < 0)
	{
		ball_p.y = 0;
		ball_dp.y *= -1;
	}

	else if (ball_p.y + ball_size > win_height)
	{
		ball_p.y = win_height - ball_size;
		ball_dp.y *= -1;
	}

	if (left_paddle_collision(player_one_p, ball_p))
	{
		ball_p.x = player_one_p.x + player_width;
		ball_dp.x *= -1;
		ball_dp.y = player_one_dp;
	}

	else if (right_paddle_collision(player_two_p, ball_p))
	{
		ball_p.x = player_two_p.x - ball_size;
		ball_dp.x *= -1;
		ball_dp.y = player_two_dp;
	}

	if (ball_p.x + ball_size < 0 || ball_p.x > win_width)
	{
		if (ball_p.x + ball_size < 0)
			right_score += 1;
		else
			left_score += 1;

		ball_p.x = (win_width - ball_size) / 2;
		ball_p.y = win_height / 2;

		int random1 = rand() % 2;
		int random2 = rand() % 2;

		if (random1 == 0)
			ball_dp.x = 1100;

		else
			ball_dp.x = -1100;

		if (random2 == 0)
			ball_dp.y = 100;

		else
			ball_dp.y = -100;
	}
}