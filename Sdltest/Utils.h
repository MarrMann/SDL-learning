#pragma once
#include <SDL_rect.h>
#include <vector>
class Utils
{
public:
	static bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

	//Box collision detection
	static bool checkCollision(SDL_Rect a, SDL_Rect b);
};

