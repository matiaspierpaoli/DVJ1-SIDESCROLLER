#include "manager/gamemanager.h"

using namespace app;

int main() 
{
	GameManager* game = new GameManager(); // Se crea una instancia de jugo que lleva al loop principal
	game->gameLoop();
	delete game; 
}