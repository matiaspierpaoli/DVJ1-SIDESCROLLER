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
		if (!pause) // Mientras no esté en pausa
		{
			player->movementOnePlayer();
		}
	}
	
	void GameManager::inputTwoPlayers()
	{
		if (!pause) // Mientras no esté en pausa
		{
			player->movementOnePlayer();
			player2->movementTwoPlayers();
		}
		
	}
	
	void GameManager::updateOnePlayer()
	{
		if (!gameOver) // Si no terminó la partida
		{
			if (IsKeyPressed('P')) pause = !pause; // Pausa con "P"

			if (!pause)
			{
				// Update
				obs->movement();
				obs->respawn();
				background->update();

				// Colisiones player 1

				if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) gameOver = true;

				if (CheckCollisionRecs(player->getRec(), obs->getRecBot()))	gameOver = true;

				// Si el obtaculo pasó al player sumar 1 al score
				if ((obs->getRecBot().x < player->getRec().x && obs->getRecBot().x > 95) && !gameOver)	scorePlayer1++;
			}
			
		}			
		else // Si terminó 
		{
			if (IsKeyPressed(KEY_ENTER)) { // Se reinicia con ENTER
				SID = screenID::onePlayer;
				resetGame();
			}
		}
	}

	void GameManager::updateTwoPlayers()
	{
		if (!gameOver) // Si no terminó la partida
		{
			if (IsKeyPressed('P')) pause = !pause; // Pausa con "P"

			if (!pause)
			{
				// Update
				obs->movement();
				obs->respawn();
				background->update();

				// Colisiones player 1

				if (CheckCollisionRecs(player->getRec(), obs->getRecTop())) activePlayer1 = false;

				if (CheckCollisionRecs(player->getRec(), obs->getRecBot())) activePlayer1 = false;

				// Si el obtaculo pasó al player sumar 1 al score de player 1
				if ((obs->getRecBot().x < player->getRec().x && obs->getRecBot().x > 95) && !gameOver && activePlayer1)	scorePlayer1++; 

				// Colisiones player 2

				if (CheckCollisionRecs(player2->getRec(), obs->getRecTop())) activePlayer2 = false;

				if (CheckCollisionRecs(player2->getRec(), obs->getRecBot())) activePlayer2 = false;

				// Si el obtaculo pasó al player sumar 1 al score de player 2
				if ((obs->getRecBot().x < player2->getRec().x && obs->getRecBot().x > 35) && !gameOver && activePlayer2) scorePlayer2++;

				// Si ambos colisionaron termina la partida
				if (activePlayer1 == false && activePlayer2 == false) gameOver = true;

			}
			
		}
		else // Si terminó 
		{
			if (IsKeyPressed(KEY_ENTER)) { // Se reinicia con ENTER
				SID = screenID::twoPlayers;
				resetGame();
			}
		}

	}

	void GameManager::drawOnePlayer()
	{		
		ClearBackground(BLACK);
		if (!gameOver) // Si no terminó la partida
		{
			background->draw(); // Fondo
			player->draw(); // Player
			obs->draw(); // Obstaculo
			DrawText(TextFormat("%4i", scorePlayer1), 20, 20, 40, GRAY); // Puntaje
			
			if (scorePlayer1 < 3) DrawText("Jump with Space", 20, GetScreenHeight() - 50, 30, GRAY); // Recordatorio para el input hasta pasar tres objetivos				
			if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY); // Pausa

			DrawText("P to pause", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 30, BLACK); // // Recordatorio para el input para pausa
		}
		else // Si terminó
		{			
			DrawText(text1, text1PositionX, text1PositionY, 40, WHITE); // You loose
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE); // Menu
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE); // Press ENTER to restart
			DrawText(TextFormat("%4i", scorePlayer1), 20, 20, 40, GRAY); // Puntaje final

			if (CheckCollisionPointRec(GetMousePosition(), rect1)) // Volver al menu
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
		
		if (!gameOver) // Si no terminó la partida
		{
			background->draw(); // Fondo
			DrawText(TextFormat("%4i", scorePlayer2), 20, 20, 40, RED); // Score de player 2
			DrawText(TextFormat("%4i", scorePlayer1), GetScreenWidth() - 100, 20, 40, GRAY); // Score de player 1

			if (activePlayer1) player->draw();	// Si no colisionó con un obstáculo, se dibuja el player 1				
			if (activePlayer2) player2->draw(); // Si no colisionó con un obstáculo, se dibuja el player 2	
		
			obs->draw(); // Obstáculo

			// Recordatorio para el input de ambos jugadores
			if (scorePlayer1 <= 3 && activePlayer1) DrawText("Jump with Space", GetScreenWidth() - 300, GetScreenHeight() - 50, 30, GRAY);
			if (scorePlayer2 <= 3 && activePlayer2) DrawText("Jump with Enter", 20, GetScreenHeight() - 50, 30, RED);

			if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY); // Pausa
			DrawText("P to pause", GetScreenWidth() / 2 - 100, GetScreenHeight() - 50, 30, BLACK);
		}
		else // Si terminó
		{
			DrawText(text4, text4PositionX, text4PositionY, 40, WHITE); // Game finished
			DrawText(text2, text2PositionX, text2PositionY, 40, WHITE); // Menu
			DrawText(text3, text3PositionX, text3PositionY, 36, WHITE); // Press ENTER to restart
			
			DrawText(TextFormat("%4i", scorePlayer1), GetScreenWidth() - 100, 20, 40, GRAY); // Score player 1
			DrawText(TextFormat("%4i", scorePlayer2), 20, 20, 40, RED); // Score player 2

			if (CheckCollisionPointRec(GetMousePosition(), rect1)) // Volver al menu
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


