#pragma once
#include "raylib.h"

class Parallax {
private:
	//Layer 1 is FRONT (Close to player, moves fastest)
	//Load AFTER WindowInit (OpenGL context needed)
	Texture2D layer1;
	Texture2D layer2;
	Texture2D layer3;
	Texture2D layer4;
public:
	Parallax();
	~Parallax();
	void draw();
};
