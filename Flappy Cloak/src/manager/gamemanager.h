#pragma once
#include "raylib.h"
#include "player/player.h"
#include "obstacle/obstacle.h"
#include "parallax/parallax.h"

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
	Parallax* background;
	const int screenWidth = 800;
	const int screenHeight = 450;

	void menuScreen();
	void gameScreen();
	void resetGame();

	void input();
	void update();
	void draw();
public:
	GameManager();
	~GameManager();
	void gameLoop();
};