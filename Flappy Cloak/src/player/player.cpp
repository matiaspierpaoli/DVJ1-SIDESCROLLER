#include "player/player.h"

Player::Player(Rectangle rec, Color color, Texture2D tex1, Texture2D tex2)
{
	this->rec = rec;
	this->color = color;
	this->tex1 = tex1;
	this->tex2 = tex2;

	falling = true;
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

	if (rec.y <= 0) rec.y = 0;	
	else if (rec.y >= GetScreenHeight()) rec.y = static_cast<float>(GetScreenHeight());
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

	if (rec.y <= 0) rec.y = 0;
	else if (rec.y >= GetScreenHeight()) rec.y = static_cast<float>(GetScreenHeight());
}

void Player::draw()
{
	if (falling)
		DrawTexture(tex1, static_cast<int>(rec.x), static_cast<int>(rec.y), WHITE);
	else
		DrawTexture(tex2, static_cast<int>(rec.x), static_cast<int>(rec.y), WHITE);
}

void Player::reset()
{
	rec.x = static_cast<float>(GetScreenWidth() / 20);
	rec.y = static_cast<float>(GetScreenHeight() / 2);
}

Rectangle Player::getRec()
{
	return rec;
}

