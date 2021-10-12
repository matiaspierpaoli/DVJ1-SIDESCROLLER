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
	recTop.x -= GetFrameTime() * 200;
	recBot.x -= GetFrameTime() * 200;
}

void Obstacle::respawn()
{
	if (recTop.x<-50 && recBot.x<-50)
	{
		recTop.x = GetScreenWidth() + 100;
		recBot.x = GetScreenWidth() + 100;
	}
}

void Obstacle::draw()
{
	DrawRectangleRec(recTop, color);
	DrawRectangleRec(recBot, color);
}

Rectangle Obstacle::getRecTop()
{
	return recTop;
}

Rectangle Obstacle::getRecBot()
{
	return recBot;
}
