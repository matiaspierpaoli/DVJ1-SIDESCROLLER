#include "player/player.h"

Player::Player(Rectangle rec, Color color, Texture2D tex1, Texture2D tex2)
{
	

	this->rec = rec;
	this->color = color;
	this->tex1 = tex1;
	this->tex2 = tex2;
}

Player::~Player()
{
}

void Player::movementOnePlayer()
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

void Player::movementTwoPlayers()
{
	if (IsKeyDown(KEY_ENTER))
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
