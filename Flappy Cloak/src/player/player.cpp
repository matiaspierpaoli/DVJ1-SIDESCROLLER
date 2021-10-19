#include "player/player.h"

Player::Player()
{
	rec.x = GetScreenWidth() / 20;
	rec.y = GetScreenHeight() / 2;
	rec.width = 40;
	rec.height = 40;
	color = GREEN;
	tex1 = LoadTexture("res/CGf1.png");
	tex2 = LoadTexture("res/CGf2.png");
}

Player::~Player()
{
}

void Player::movement()
{
	if (IsKeyDown(KEY_SPACE))
	{
		rec.y -= GetFrameTime() * 300;
		falling = true;
	}
	else
	{
		rec.y += GetFrameTime() * 170;
		falling = false; 
	}
}

void Player::draw()
{
	if (falling)
		DrawTexture(tex1, rec.x, rec.y, WHITE);
	else
		DrawTexture(tex2, rec.x, rec.y, WHITE);
}

void Player::reset()
{
	rec.x = GetScreenWidth() / 20;
	rec.y = GetScreenHeight() / 2;
}

Rectangle Player::getRec()
{
	return rec;
}
