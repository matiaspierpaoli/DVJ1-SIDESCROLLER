#include "player/player.h"

Player::Player()
{
	rec.x = GetScreenWidth() / 20;
	rec.y = GetScreenWidth() / 2;
	rec.width = 40;
	rec.height = 40;
	color = SKYBLUE;
}

Player::~Player()
{
}

void Player::movement()
{
	if (IsKeyDown(KEY_W))rec.y -= GetFrameTime() * 420;
	if (IsKeyDown(KEY_S))rec.y += GetFrameTime() * 420;
}

void Player::draw()
{
	DrawRectangleRec(rec, color);
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
