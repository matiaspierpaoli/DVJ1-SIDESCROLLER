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
	if (IsKeyDown(KEY_SPACE)) // Si se presiona el espacio
	{
		rec.y -= GetFrameTime() * 300; // Sube en y
		falling = true;
	}
	else // SIi no se presiona
	{
		rec.y += GetFrameTime() * 170; // Baja en y
		falling = false; 
	}

	if (rec.y <= 0) rec.y = 0;	// Si toca el techo no sube más
	else if (rec.y >= GetScreenHeight()) rec.y = static_cast<float>(GetScreenHeight()); // Si toca el piso no baja más
}

void Player::movementTwoPlayers()
{
	if (IsKeyDown(KEY_ENTER)) // Si se presiona el espacio
	{
		rec.y -= GetFrameTime() * 300; // Sube en y
		falling = true;
	}
	else // SIi no se presiona
	{
		rec.y += GetFrameTime() * 170; // Baja en y
		falling = false;
	}

	if (rec.y <= 0) rec.y = 0; // Si toca el techo no sube más
	else if (rec.y >= GetScreenHeight()) rec.y = static_cast<float>(GetScreenHeight()); // Si toca el piso no baja más
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

