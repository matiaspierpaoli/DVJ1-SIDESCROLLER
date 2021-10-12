#pragma once
#include "raylib.h"

class Obstacle {
private:
	int gap;
	Rectangle recTop;
	Rectangle recBot;
	Color color;
public:
	Obstacle();
	~Obstacle();
	void movement();
	void respawn();
	void draw();
	Rectangle getRecTop();
	Rectangle getRecBot();
};