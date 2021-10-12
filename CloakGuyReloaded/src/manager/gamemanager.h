#pragma once
#include "raylib.h"

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