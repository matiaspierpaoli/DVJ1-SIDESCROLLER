#pragma once
#include "raylib.h"
#include "player/player.h"
#include "obstacle/obstacle.h"
#include "parallax/parallax.h"

	enum class screenID 
	{
		menu,
		onePlayer,
		twoPlayers,
		exit
	};


class GameManager
{
private:
	screenID SID;
	Player* player;
	Player* player2;
	Obstacle* obs;
	Parallax* background;
	const int screenWidth = 800;
	const int screenHeight = 450;

	void menuScreen();
	void gameScreenOnePlayer();
	void gameScreenTwoPlayers();
	void resetGame();

	void inputOnePlayer();
	void updateOnePlayer();
	void drawOnePlayer();
	
	void inputTwoPlayers();
	void updateTwoPlayers();
	void drawTwoPlayers();

public:
	GameManager();
	~GameManager();
	void gameLoop();	
};