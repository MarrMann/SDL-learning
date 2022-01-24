#pragma once
#include <SDL_rect.h>
class Utils
{
public:
	//Box collision detection
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
};

