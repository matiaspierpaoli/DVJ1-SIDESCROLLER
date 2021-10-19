#pragma once
#include "raylib.h"
class Player {
private:
	Rectangle rec;
	Color color;
	Texture2D tex1;
	Texture2D tex2;
	bool falling;
public:
	Player();
	~Player();
	void movement();
	void draw();
	void reset();

	Rectangle getRec();
};