#include "manager/gamemanager.h"

using namespace app;

int main()
{
	GameManager* game = new GameManager();
	game->gameLoop();
	delete game;
}