#include "manager/gamemanager.h"

using namespace app;

void main(){
GameManager* game = new GameManager();
	game->gameLoop();
	delete game;
}