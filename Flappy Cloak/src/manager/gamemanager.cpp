#include "gamemanager.h"

using namespace app;
using namespace menu;

namespace app
{
	bool exit = false;
	screenID SID = screenID::menu;

	static char text1[] = "You loose";
	static char text2[] = "Menu";
	static char text3[] = "Press Enter to restart";
	static char text4[] = "Game Finished";

	static int scorePlayer1;
	static int scorePlayer2;

	static bool pause;

	static Rectangle rect1;
	static Color colorRect;

	static int text1PositionY;
	static int text1PositionX;
	static int text2PositionX;
	static int text2PositionY;
	static int text3PositionX;
	static int text3PositionY;
	static int text4PositionY;
	static int text4PositionX;

	GameManager::GameManager()
	{
		SetExitKey(0);
		InitWindow(screenWidth, screenHeight, "Flappy Cloak");
		SetTargetFPS(60);
		

		Rectangle rec;
		Color color;
		Texture2D tex1;
		Texture2D tex2;		

		colorRect = GRAY;

		pause = false;

		rect1.height = 45.0f;
		rect1.width = 100.0f;
		rect1.x = GetScreenWidth() / 2 - rect1.width / 2;
		rect1.y = static_cast<float>(GetScreenHeight() * 0.70);

		// You loose
		text1PositionX = GetScreenWidth() / 2 - MeasureText(text1, 40) / 2;
		text1PositionY = static_cast<int>(GetScreenHeight() * 0.50f);

		// Menu
		text2PositionX = GetScreenWidth() / 2 - MeasureText(text2, 40) / 2;
		text2PositionY = static_cast<int>(rect1.y);

		// Press Enter to return to Menu
		text3PositionX = static_cast<int>(GetScreenWidth() / 2 - MeasureText(text3, 36) / 2);
		text3PositionY = static_cast<int>(GetScreenHeight() * 0.90f);

		// Game Finished
		text4PositionX = static_cast<int>(GetScreenWidth() / 2 - MeasureText(text4, 40) / 2);
		text4PositionY = static_cast<int>(GetScreenHeight() * 0.50f);


		rec.x = static_cast<float>(GetScreenWidth() / 20 + 60);
		rec.y = static_cast<float>(GetScreenHeight() / 2);
		rec.width = 40.0f;
		rec.height = 40.0f;
		color = GREEN;
		tex1 = LoadTexture("res/CGf1.png");
		tex2 = LoadTexture("res/CGf2.png");

		player = new Player(rec, color, tex1, tex2);

		rec.x = static_cast<float>(GetScreenWidth() / 20);
		rec.y = static_cast<float>(GetScreenHeight() / 2);
		rec.width = 40.0f;
		rec.height = 40.0f;
		color = GREEN;
		tex1 = LoadTexture("res/pixil-frame-0_1.png");
		tex2 = LoadTexture("res/pixil-frame-0_2.png");

		player2 = new Player(rec, color, tex1, tex2);

		obs = new Obstacle();
		background = new Parallax();

		gameOver = false;
		activePlayer1 = true;
		activePlayer2 = true;
	}

	GameManager::~GameManager()
	{
		CloseWindow();
		delete player;
		delete player2;
		delete obs;
		delete background;
	}

	void GameManager::gameLoop()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		initMenu();

		// Main game loop
		while (!WindowShouldClose() && !exit)
		{
			updateGame();
			drawGame();
		}

		CloseWindow();
	}

	void GameManager::resetGame()
	{
		player->reset();
		player2->reset();
		obs->reset();
		gameOver = false;
		activePlayer1 = true;
		activePlayer2 = true;
		scorePlayer1 = 0;
		scorePlayer2 = 0;
	}

	void GameManager::updateGame()
	{
		switch (SID)
		{		
		case screenID::menu:
			updateMenu();
			break;		
		case screenID::onePlayer:
			inputOnePlayer();
			updateOnePlayer();
			break;
		case screenID::twoPlayers:
			inputTwoPlayers();
			updateTwoPlayers();
			break;
		default:
			break;
		}

	}

	void GameManager::drawGame()
	{
		BeginDrawing();
		switch (SID)
		{			
		case screenID::menu:
			drawMenu();
			break;
		case screenID::onePlayer:
			drawOnePlayer();
			break;
		case screenID::twoPlayers:
			drawTwoPlayers();
			break;
		default:
			break;
		}
		EndDrawing(); 
	}

	void GameManager::inputOnePlayer()
	{
		if (!pause)
		{
			player->movementOnePlayer();
		}
	}
	
	void GameManager::inputTwoPlayers()
	{
		if (!pause)
		{
			player->movementOnePlayer();
			player2->movementTwoPlayers();
		}
		
	}
	
	void GameManager::updateOnePlayer()
	{
		if (!gameOver)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				obs->movement();
				obs->respawn();
				background->update();

				if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) gameOver = true;

				if (CheckCollisionRecs(player->getRec(), obs->getRecBot()))	gameOver = true;

				if ((obs->getRecBot().x < player->getRec().x && obs->getRecBot().x > 95) && !gameOver)	scorePlayer1++;
			}
			
		}			
		else
		{
			if (IsKeyPressed(KEY_ENTER)) {
				SID = screenID::onePlayer;
				resetGame();
			}
		}
	}

	void GameManager::updateTwoPlayers()
	{
		if (!gameOver)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				obs->movement();
				obs->respawn();
				background->update();

				if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) activePlayer1 = false;

				if (CheckCollisionRecs(player->getRec(), obs->getRecBot())) activePlayer1 = false;

				if ((obs->getRecBot().x < player->getRec().x && obs->getRecBot().x > 95) && !gameOver && activePlayer1)	scorePlayer1++;

				if (CheckCollisionRecs(player2->getRec(), obs->getRecTop())) activePlayer2 = false;

				if (CheckCollisionRecs(player2->getRec(), obs->getRecBot())) activePlayer2 = false;

				if ((obs->getRecBot().x < player2->getRec().x && obs->getRecBot().x > 35) && !gameOver && activePlayer2) scorePlayer2++;

				if (activePlayer1 == false && activePlayer2 == false) gameOver = true;

			}
			
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER)) {
				SID = screenID::twoPlayers;
				resetGame();
			}
		}

	}

	void GameManager::drawOnePlayer()
	{		
		ClearBackground(BLACK);
		if (!gameOver)
		{
			background->draw();
			player->draw();
			obs->draw();
			DrawText(TextFormat("%4i", scorePlayer1), 20, 20, 40, GRAY);
			
			if (scorePlayer1 < 3) DrawText("Jump with Space", 20, GetScreenHeight() - 50, 30, GRAY);				
			if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);

			DrawText("P to pause", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 30, BLACK);
		}
		else
		{			
			DrawText(text1, text1PositionX, text1PositionY, 40, WHITE);
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE);
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE);
			DrawText(TextFormat("%4i", scorePlayer1), 20, 20, 40, GRAY);

			if (CheckCollisionPointRec(GetMousePosition(), rect1))
			{
				DrawText(text2, text2PositionX, text2PositionY, 40, RED);

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					SID = screenID::menu;
					resetGame();
					initMenu();
				}
			}
		}				
	}

	void GameManager::drawTwoPlayers()
	{		
		ClearBackground(BLACK);
		
		if (!gameOver)
		{
			background->draw();
			DrawText(TextFormat("%4i", scorePlayer2), 20, 20, 40, RED);
			DrawText(TextFormat("%4i", scorePlayer1), GetScreenWidth() - 100, 20, 40, GRAY);

			if (activePlayer1) player->draw();						
			if (activePlayer2) player2->draw();
		
			obs->draw();

			if (scorePlayer1 <= 3 && activePlayer1) DrawText("Jump with Space", GetScreenWidth() - 300, GetScreenHeight() - 50, 30, GRAY);
			if (scorePlayer2 <= 3 && activePlayer2) DrawText("Jump with Enter", 20, GetScreenHeight() - 50, 30, RED);

			if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
			DrawText("P to pause", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 30, BLACK);
		}
		else
		{
			DrawText(text4, text4PositionX, text4PositionY, 40, WHITE);
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE);
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE);

			DrawText(TextFormat("%4i", scorePlayer1), 20, 20, 40, GRAY);
			DrawText(TextFormat("%4i", scorePlayer2), GetScreenWidth() - 20, 20, 40, RED);

			if (CheckCollisionPointRec(GetMousePosition(), rect1))
			{
				DrawText(text2, text2PositionX, text2PositionY, 40, RED);

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					SID = screenID::menu;
					resetGame();
					initMenu();
				}
			}
		}
	}
}


