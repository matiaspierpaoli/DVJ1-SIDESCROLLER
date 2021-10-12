#include "obstacle.h"

Obstacle::Obstacle()
{
	gap = 90; //Player size * 3
	recTop.x = GetScreenWidth() + 100;
	recTop.y = 0;
	recTop.width = GetScreenWidth() / 10;
	recTop.height = (GetScreenHeight() / 2) - gap;


	recBot.width = GetScreenWidth() / 10;
	recBot.height = (GetScreenHeight() / 2) + gap;
	recBot.x = GetScreenWidth() + 100;
	recBot.y = (GetScreenHeight() / 2) + gap;
}

Obstacle::~Obstacle()
{
}

void Obstacle::movement()
{
}

void Obstacle::respawn()
{
}

void Obstacle::draw()
{
}
