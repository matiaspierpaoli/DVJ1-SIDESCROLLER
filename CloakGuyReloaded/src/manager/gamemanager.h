#pragma once
#include "raylib.h"
#include "player/player.h"
#include "obstacle/obstacle.h"

	enum class screenID 
	{
		menu,
		game,
		exit
	};


class GameManager
{
private:
	screenID SID;
	Player* player;
	Obstacle* obs;
	const int screenWidth = 800;
	const int screenHeight = 450;
public:
	GameManager();
	~GameManager();
	void gameLoop();
	void menuScreen();
	void gameScreen();

	void input();
	void update();
	void draw();
};