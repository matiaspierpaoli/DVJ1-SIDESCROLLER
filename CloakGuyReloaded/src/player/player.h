#pragma once
#include "raylib.h"
class Player {
private:
	Rectangle rec;
	Color color;
public:
	Player();
	~Player();
	void movement();
	void draw();
};