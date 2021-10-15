#include "parallax.h"


Parallax::Parallax()
{
	layer1 = LoadTexture("res/Clouds1.png");
	layer2 = LoadTexture("res/Mountains2.png");
	layer3 = LoadTexture("res/Clouds3.png");
	layer4 = LoadTexture("res/Sky4.png");
}

Parallax::~Parallax()
{

}

void Parallax::draw()
{
	DrawTextureEx(layer4, { 0, 0 },0, 2.2f, BLUE);
	DrawTextureEx(layer3, { 0, 0 },0, 2.2f, RED);
	DrawTextureEx(layer2, { 0, 0 },0, 2.2f, BLACK);
	DrawTextureEx(layer1, { 0, 0 },0, 2.2f, BLUE);
}
