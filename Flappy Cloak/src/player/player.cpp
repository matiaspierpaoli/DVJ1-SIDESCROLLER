#include "player/player.h"

Player::Player()
{
	rec.x = GetScreenWidth() / 20;
	rec.y = GetScreenWidth() / 2;
	rec.width = 40;
	rec.height = 40;
	color = GREEN;
	tex = LoadTexture("res/CloakGuy.png");
}

Player::~Player()
{
}

void Player::movement()
{
	if (IsKeyDown(KEY_W))rec.y -= GetFrameTime() * 420;
	if (IsKeyDown(KEY_S))rec.y += GetFrameTime() * 420;

	if (IsKeyDown(KEY_SPACE))
		rec.y -= GetFrameTime() * 300;
	else
		rec.y += GetFrameTime() * 170;
}

void Player::draw()
{
	DrawTexture(tex, rec.x, rec.y, WHITE);
}

void Player::reset()
{
	rec.x = GetScreenWidth() / 20;
	rec.y = GetScreenWidth() / 2;
}

Rectangle Player::getRec()
{
	return rec;
}
