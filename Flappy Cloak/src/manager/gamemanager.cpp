#include "gamemanager.h"

GameManager::GameManager()
{
	SID = screenID::game;


	InitWindow(screenWidth, screenHeight, "Flappy Cloak");
	SetTargetFPS(60);
	player = new Player();
	obs = new Obstacle();
}

GameManager::~GameManager()
{
}

void GameManager::gameLoop()
{
	while (!WindowShouldClose()) {
		switch (SID) {
			break;
		case screenID::menu:
			menuScreen();
			break;
		case screenID::game:
			gameScreen();
			break;
		}
	}
}

void GameManager::menuScreen()
{
	Rectangle playButton;
	playButton.x = GetScreenWidth() / 100 * 2.5f;
	playButton.y = GetScreenHeight() / 2;
	playButton.height = 30;
	playButton.width = 65;
	Rectangle creditsButton;
	creditsButton.x = GetScreenWidth() / 100 * 2.5f;
	creditsButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 22.2f);
	creditsButton.height = 30;
	creditsButton.width = 113;
	Rectangle closeButton;
	closeButton.x = GetScreenWidth() / 100 * 2.5f;
	closeButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 37.3f);
	closeButton.height = 30;
	closeButton.width = 81.25f;

	while (!WindowShouldClose() && SID == screenID::menu) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(FormatText("Flap"), 20, GetScreenHeight() / 10, 120, SKYBLUE);

		if (CheckCollisionPointRec(GetMousePosition(), playButton))
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, RED);
		else
			DrawText(FormatText("Play"), 20, GetScreenHeight() / 2, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
		else
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton))
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
		else
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);

		DrawText(FormatText("v 0.1"), GetScreenWidth() - 50, 1, 20, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			SID = screenID::game;
		}

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
			DrawText(FormatText("Engine: Raylib 3.7"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 20, 30, WHITE);
			DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 100, 30, WHITE);
			DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 130, 30, WHITE);
		}

		if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			//exit(0);
		}

		EndDrawing();

		if (WindowShouldClose())
			SID = screenID::exit;
	}
}

void GameManager::gameScreen()
{
	resetGame();
	while (!WindowShouldClose()&&SID == screenID::game)
	{
		input();
		update();
		draw();
	}

}
void GameManager::resetGame()
{
	player->reset();
	obs->reset();
}

void GameManager::input()
{
	player->movement();
}

void GameManager::update()
{
	obs->movement();
	obs->respawn();
	if (CheckCollisionRecs(player->getRec(), obs->getRecTop()))
		SID = screenID::menu;

	if(CheckCollisionRecs(player->getRec(), obs->getRecBot()))
		SID = screenID::menu;
}

void GameManager::draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	player->draw();
	obs->draw();
	EndDrawing();
}
