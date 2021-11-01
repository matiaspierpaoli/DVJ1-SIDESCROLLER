#include "menu/menu.h"
#include "manager/gamemanager.h"

using namespace app;

namespace app
{
	namespace menu
	{
		Rectangle onePlayerButton;
		Rectangle twoPlayersButton;
		Rectangle controllesButton;
		Rectangle creditsButton;
		Rectangle closeButton;

		void initMenu()
		{
			onePlayerButton.x = GetScreenWidth() / 100 * 2.5f;
			onePlayerButton.y = static_cast<float>(GetScreenHeight() / 2 - 30);
			onePlayerButton.height = 30;
			onePlayerButton.width = 120;

			twoPlayersButton.x = GetScreenWidth() / 100 * 2.5f;
			twoPlayersButton.y = static_cast<float>(GetScreenHeight() / 2 + 20);
			twoPlayersButton.height = 30.0f;
			twoPlayersButton.width = 150.0f;

			controllesButton.x = GetScreenWidth() / 100 * 2.5f;
			controllesButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 16.2f);
			controllesButton.height = 30.0f;
			controllesButton.width = 190.0f;

			creditsButton.x = GetScreenWidth() / 100 * 2.5f;
			creditsButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 28.0f);
			creditsButton.height = 30;
			creditsButton.width = 113;

			closeButton.x = GetScreenWidth() / 100 * 2.5f;
			closeButton.y = (GetScreenHeight() / 2) + (GetScreenHeight() / 100 * 40.0f); 
			closeButton.height = 30.0f;
			closeButton.width = 81.25f;
		}

		void updateMenu()
		{
			if (CheckCollisionPointRec(GetMousePosition(), onePlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {								
				SID = screenID::onePlayer;
			}
			
			if (CheckCollisionPointRec(GetMousePosition(), twoPlayersButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				SID = screenID::twoPlayers;						
			}

			if (CheckCollisionPointRec(GetMousePosition(), creditsButton)) {
				DrawText(FormatText("Engine: Raylib 3.7"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 20, 30, WHITE);
				DrawText(FormatText("Created by:"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 100, 30, WHITE);
				DrawText(FormatText("Matias P. Karplus"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 130, 30, WHITE);
				DrawText(FormatText("Matias Pierpaoli"), (GetScreenWidth() / 2 + 40), (GetScreenHeight() / 4) + 160, 30, WHITE);
			}

			if (CheckCollisionPointRec(GetMousePosition(), controllesButton)) {
				DrawText(FormatText("Player 1 jumps with Space"), (GetScreenWidth() / 2), (GetScreenHeight() / 4) + 20, 28, GRAY);
				DrawText(FormatText("Player 2 jumps with Enter"), (GetScreenWidth() / 2), (GetScreenHeight() / 4) + 100, 28, RED);
			}

			if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				exit = true;
			}
		}

		void drawMenu()
		{
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
				DrawText(FormatText("Key Bindings"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 16.2f)), 30, RED);
			else
				DrawText(FormatText("Key Bindings"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 16.2f)), 30, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), creditsButton))
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 28.0f)), 30, RED);
			else
				DrawText(FormatText("Credits"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 28.0f)), 30, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), closeButton))
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 40.0f)), 30, RED);
			else
				DrawText(FormatText("Close"), 20, (GetScreenHeight() / 2) + static_cast<int>((GetScreenHeight() / 100 * 40.0f)), 30, WHITE);

			DrawText(FormatText("v 1.0"), GetScreenWidth() - 50, 1, 20, WHITE);

		}
	}
}


