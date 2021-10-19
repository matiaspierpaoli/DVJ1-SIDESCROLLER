#pragma once
#include "raylib.h"
class Player {
private:
	Rectangle rec;
	Color color;
	Texture2D tex;
public:
	Player();
	~Player();
	void movement();
	void draw();
	void reset();

	Rectangle getRec();
};