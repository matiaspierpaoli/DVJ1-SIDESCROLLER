#include "parallax.h"


Parallax::Parallax()
{
	layer1 = LoadTexture("res/Clouds1.png");
	layer2 = LoadTexture("res/Mountains2.png");
	layer3 = LoadTexture("res/Clouds3.png");
	layer4 = LoadTexture("res/Sky4.png");
	l1 = {0,0};
	l2 = {0,0};
	l3 = {0,0};
	l4 = {0,0};
}

Parallax::~Parallax()
{

}

void Parallax::draw()
{
	DrawTextureEx(layer4, l4,0, 2.2f, WHITE);
	DrawTextureEx(layer3, l3,0, 2.2f, WHITE);
	DrawTextureEx(layer2, l2,0, 2.2f, WHITE);
	DrawTextureEx(layer1, l1,0, 2.2f, WHITE);
}

void Parallax::update() 
{
	l1.x -= GetFrameTime() * 100;
	l2.x -= GetFrameTime() * 50;
	l3.x -= GetFrameTime() * 10;
	l4.x -= GetFrameTime() * 5;
}
