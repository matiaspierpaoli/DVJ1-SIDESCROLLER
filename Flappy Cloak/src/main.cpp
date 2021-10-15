#include "manager/gamemanager.h"

void main(){
GameManager* game = new GameManager();
	game->gameLoop();
	delete game;
}