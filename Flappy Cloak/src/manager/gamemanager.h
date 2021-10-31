#pragma once
#include "raylib.h"
#include "player/player.h"
#include "obstacle/obstacle.h"
#include "parallax/parallax.h"
#include "menu/menu.h"

#include <iostream>
#include <time.h>

namespace app
{
	enum class screenID
	{
		menu,
		onePlayer,
		twoPlayers,		
	};

	extern screenID SID;
	extern bool exit;

	class GameManager
	{
	private:
		
		Player* player;
		Player* player2;
		Obstacle* obs;
		Parallax* background;
		const int screenWidth = 800;
		const int screenHeight = 450;

		bool gameOver;
		bool activePlayer1;
		bool activePlayer2;

		void resetGame();

		void drawGame();		
		void updateGame();


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
}
