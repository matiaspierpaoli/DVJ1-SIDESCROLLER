#pragma once
#include "raylib.h"

class Obstacle {
private:
	Rectangle recTop;
	Rectangle recBot;
	Color color;
public:
	Obstacle();
	~Obstacle();
	void movement();
	void respawn();
	void draw();
};