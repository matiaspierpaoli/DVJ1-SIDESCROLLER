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

	static int scaleAux2;
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
		InitWindow(screenWidth, screenHeight, "Flappy Cloak");
		SetTargetFPS(60);
		SetExitKey(0);

		Rectangle rec;
		Color color;
		Texture2D tex1;
		Texture2D tex2;		

		colorRect = GRAY;

		scaleAux2 = 1600;

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


		rec.x = GetScreenWidth() / 20;
		rec.y = GetScreenHeight() / 2;
		rec.width = 40;
		rec.height = 40;
		color = GREEN;
		tex1 = LoadTexture("res/CGf1.png");
		tex2 = LoadTexture("res/CGf2.png");

		player = new Player(rec, color, tex1, tex2);

		rec.x = GetScreenWidth() / 20;
		rec.y = GetScreenHeight() / 2;
		rec.width = 40;
		rec.height = 40;
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
	}

	void GameManager::resetGame()
	{
		player->reset();
		player2->reset();
		obs->reset();
		gameOver = false;
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
		player->movementOnePlayer();		
	}
	
	void GameManager::inputTwoPlayers()
	{
		player->movementOnePlayer();
		player2->movementTwoPlayers();
		
	}
	
	void GameManager::updateOnePlayer()
	{
		obs->movement();
		obs->respawn();
		background->update();
		
		if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) gameOver = true;
					
		if (CheckCollisionRecs(player->getRec(), obs->getRecBot()))	gameOver = true;		

		if (gameOver)
		{
			if (IsKeyPressed(KEY_ENTER)) {
				SID = screenID::onePlayer;
				resetGame();
			}
		}
	}

	void GameManager::updateTwoPlayers()
	{
		obs->movement();
		obs->respawn();
		background->update();
		
		if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) activePlayer1 = false;

		if (CheckCollisionRecs(player->getRec(), obs->getRecBot())) activePlayer1 = false;

		if (CheckCollisionRecs(player2->getRec(), obs->getRecTop())) activePlayer2 = false;

		if (CheckCollisionRecs(player2->getRec(), obs->getRecBot())) activePlayer2 = false;
			
		if (activePlayer1 == false && activePlayer2 == false) gameOver = true;

		if (gameOver)
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
		}
		else
		{			
			DrawText(text1, text1PositionX, text1PositionY, 40, WHITE);
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE);
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE);

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

			if (activePlayer1) player->draw();			
			
			if (activePlayer2) player2->draw();
		
			obs->draw();
		}
		else
		{
			DrawText(text4, text4PositionX, text4PositionY, 40, WHITE);
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE);
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE);

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


