#include "gamemanager.h"

GameManager::GameManager()
{
	SID = screenID::menu;
	InitWindow(screenWidth, screenHeight, "Flappy Cloak");
	SetTargetFPS(60);
	SetExitKey(KEY_ESCAPE);
	player = new Player();
	obs = new Obstacle();
	background = new Parallax();
}

GameManager::~GameManager()
{
	CloseWindow();
	delete player;
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
	onePlayerButton.y = GetScreenHeight() / 2;
	onePlayerButton.height = 30;
	onePlayerButton.width = 120;
	Rectangle twoPlayersButton;
	twoPlayersButton.x = GetScreenWidth() / 100 * 2.5f;
	twoPlayersButton.y = GetScreenHeight() / 2 + 50;
	twoPlayersButton.height = 30;
	twoPlayersButton.width = 150;
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

		if (CheckCollisionPointRec(GetMousePosition(), onePlayerButton))
			DrawText(FormatText("1 Player"), 20, GetScreenHeight() / 2, 30, RED);
		else
			DrawText(FormatText("1 Player"), 20, GetScreenHeight() / 2, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), twoPlayersButton))
			DrawText(FormatText("2 Players"), 20, GetScreenHeight() / 2 + 50, 30, RED);
		else
			DrawText(FormatText("2 Players"), 20, GetScreenHeight() / 2 + 50, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, RED);
		else
			DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + 100, 30, WHITE);

		if (CheckCollisionPointRec(GetMousePosition(), closeButton))
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, RED);
		else
			DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + 150, 30, WHITE);

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
	if (WindowShouldClose())
		SID = screenID::exit;
}

void GameManager::update()
{
	obs->movement();
	obs->respawn();
	background->update();
	if (CheckCollisionRecs(player->getRec(), obs->getRecTop()))
		SID = screenID::menu;

	if(CheckCollisionRecs(player->getRec(), obs->getRecBot()))
		SID = screenID::menu;
}

void GameManager::draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	background->draw();
	player->draw();
	obs->draw();
	EndDrawing();
}
