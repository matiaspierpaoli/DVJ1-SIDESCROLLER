#include "gamemanager.h"

GameManager::GameManager()
{
	SID = screenID::menu;
	InitWindow(screenWidth, screenHeight, "Flappy Cloak");
	SetTargetFPS(60);
	SetExitKey(KEY_ESCAPE);

	Rectangle rec;
	Color color;
	Texture2D tex1;
	Texture2D tex2;

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
	while (!WindowShouldClose()) {
		switch (SID) {
			break;
		case screenID::menu:
			menuScreen();
			break;
		case screenID::onePlayer:
			gameScreenOnePlayer();
			break;
		case screenID::twoPlayers:
			gameScreenTwoPlayers();
			break;
		case screenID::exit:
			CloseWindow();
			break;
		}
	}
}

void GameManager::menuScreen()
{
	Rectangle onePlayerButton;
	onePlayerButton.x = GetScreenWidth() / 100 * 2.5f;
	onePlayerButton.y = GetScreenHeight() / 2 - 30;
	onePlayerButton.height = 30;
	onePlayerButton.width = 120;
	Rectangle twoPlayersButton;
	twoPlayersButton.x = GetScreenWidth() / 100 * 2.5f;
	twoPlayersButton.y = GetScreenHeight() / 2 + 20;
	twoPlayersButton.height = 30;
	twoPlayersButton.width = 150;
	Rectangle controllesButton;
	controllesButton.x = GetScreenWidth() / 100 * 2.5f;
	controllesButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 16.2f);
	controllesButton.height = 30;
	controllesButton.width = 190;
	Rectangle creditsButton;
	creditsButton.x = GetScreenWidth() / 100 * 2.5f;
	creditsButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 28.0f);
	creditsButton.height = 30;
	creditsButton.width = 113;
	Rectangle closeButton;
	closeButton.x = GetScreenWidth() / 100 * 2.5f;
	closeButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 40.0f); //37.3
	closeButton.height = 30;
	closeButton.width = 81.25f;

	while (!WindowShouldClose() && SID == screenID::menu) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(FormatText("Flap"), 20, GetScreenHeight() / 10, 120, SKYBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), onePlayerButton))
			DrawText(FormatText("1 Player"), 20, GetScreenHeight() / 2 - 30, 30, RED);
		else
			DrawText(FormatText("1 Player"), 20, GetScreenHeight() / 2 - 30, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), twoPlayersButton))
			DrawText(FormatText("2 Players"), 20, GetScreenHeight() / 2 + 20, 30, RED);
		else
			DrawText(FormatText("2 Players"), 20, GetScreenHeight() / 2 + 20, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), controllesButton))
			DrawText(FormatText("Key Bindings"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 16.2f), 30, RED);
		else
			DrawText(FormatText("Key Bindings"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 16.2f), 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 28.0f), 30, RED);
		else
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 28.0f), 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton))
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 40.0f), 30, RED);
		else
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 40.0f), 30, WHITE);

		DrawText(FormatText("v 0.3"), GetScreenWidth() - 50, 1, 20, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), onePlayerButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			SID = screenID::onePlayer;
		}

		if (CheckCollisionPointRec(GetMousePosition(), twoPlayersButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			SID = screenID::twoPlayers;
		}

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
			DrawText(FormatText("Engine: Raylib 3.7"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 20, 30, WHITE);
			DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 100, 30, WHITE);
			DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 130, 30, WHITE);
			DrawText(FormatText("Matias Pierpaoli"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 160, 30, WHITE);
		}

		if (CheckCollisionPointRec(GetMousePosition(), controllesButton)) {
			DrawText(FormatText("Player 1 jumps with Space"), (GetScreenWidth() / 2), (GetScreenHeight() / 4) + 20, 28, WHITE);
			DrawText(FormatText("Player 2 jumps with Enter"), (GetScreenWidth() / 2), (GetScreenHeight() / 4) + 100, 28, WHITE);			
		}

		if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			//exit(0);
		}

		EndDrawing();

		if (WindowShouldClose())
			SID = screenID::exit;
	}
}

void GameManager::gameScreenOnePlayer()
{
	resetGame();
	while (!WindowShouldClose()&&SID == screenID::onePlayer)
	{
		inputOnePlayer();
		updateOnePlayer();
		drawOnePlayer();
	}

}
void GameManager::gameScreenTwoPlayers()
{
	resetGame();
	while (!WindowShouldClose() && SID == screenID::twoPlayers)
	{
		inputTwoPlayers();
		updateTwoPlayers();
		drawTwoPlayers();
	}

}
void GameManager::resetGame()
{
	player->reset();
	player2->reset();
	obs->reset();
}

void GameManager::inputOnePlayer()
{
	player->movementOnePlayer();
	if (WindowShouldClose())
		SID = screenID::exit;
}
void GameManager::inputTwoPlayers()
{
	player->movementOnePlayer();
	player2->movementTwoPlayers();
	if (WindowShouldClose())
		SID = screenID::exit;
}
void GameManager::updateOnePlayer()
{
	obs->movement();
	obs->respawn();
	background->update();
	if (CheckCollisionRecs(player->getRec(), obs->getRecTop()))
		SID = screenID::menu;

	if(CheckCollisionRecs(player->getRec(), obs->getRecBot()))
		SID = screenID::menu;
}

void GameManager::updateTwoPlayers()
{
	obs->movement();
	obs->respawn();
	background->update();
	if (CheckCollisionRecs(player->getRec(), obs->getRecTop()))
		SID = screenID::menu;

	if (CheckCollisionRecs(player->getRec(), obs->getRecBot()))
		SID = screenID::menu;
	
	if (CheckCollisionRecs(player2->getRec(), obs->getRecTop()))
		SID = screenID::menu;

	if (CheckCollisionRecs(player2->getRec(), obs->getRecBot()))
		SID = screenID::menu;

}

void GameManager::drawOnePlayer()
{
	BeginDrawing();
	ClearBackground(BLACK);
	background->draw();
	player->draw();
	obs->draw();
	EndDrawing();
}

void GameManager::drawTwoPlayers()
{
	BeginDrawing();
	ClearBackground(BLACK);
	background->draw();
	player->draw();
	player2->draw();
	obs->draw();
	EndDrawing();
}
