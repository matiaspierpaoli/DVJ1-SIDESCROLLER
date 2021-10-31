#include "obstacle.h"

Obstacle::Obstacle()
{
	gap = 90; //Player size * 3
	recTop.x = static_cast<float>(GetScreenWidth() + 100);
	recTop.y = 0.0f;
	recTop.width = static_cast<float>(GetScreenWidth() / 10);
	recTop.height = static_cast<float>((GetScreenHeight() / 2) - gap);

	recBot.width = static_cast<float>(GetScreenWidth() / 10);
	recBot.height = static_cast<float>((GetScreenHeight() / 2) + gap);
	recBot.x = static_cast<float>(GetScreenWidth() + 100);
	recBot.y = static_cast<float>((GetScreenHeight() / 2) + gap);
	
	color = RED;
}

Obstacle::~Obstacle()
{
}

void Obstacle::movement()
{
	recTop.x -= GetFrameTime() * 300;
	recBot.x -= GetFrameTime() * 300;
}

void Obstacle::respawn()
{
	if (recTop.x<-100 && recBot.x<-100)
	{
		recTop.x = static_cast<float>(GetScreenWidth() + 100);
		recBot.x = static_cast<float>(GetScreenWidth() + 100);
	}
}

void Obstacle::draw()
{
	DrawRectangleRec(recTop, color);
	DrawRectangleRec(recBot, color);
}

void Obstacle::reset()
{
	recTop.x = static_cast<float>(GetScreenWidth() + 100);
	recTop.y = 0.0f;
	recTop.width = static_cast<float>(GetScreenWidth() / 10);
	recTop.height = static_cast<float>((GetScreenHeight() / 2) - gap);

	recBot.width = static_cast<float>(GetScreenWidth() / 10);
	recBot.height = static_cast<float>((GetScreenHeight() / 2) + gap);
	recBot.x = static_cast<float>(GetScreenWidth() + 100);
	recBot.y = static_cast<float>((GetScreenHeight() / 2) + gap);
}

Rectangle Obstacle::getRecTop()
{
	return recTop;
}

Rectangle Obstacle::getRecBot()
{
	return recBot;
}
