#pragma once
#include <SDL_rect.h>
#include <vector>
#include "Dot.h"

class Utils
{
public:
	static bool checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b);

	//Box collision detection
	static bool checkCollision(SDL_Rect a, SDL_Rect b);

	//Circle/circle collision detection
	static bool checkCollision(Circle& a, Circle& b);

	//Circle/box collision
	static bool checkCollision(Circle& a, SDL_Rect& b);

	//Calculates distance between two points
	static double distanceSquared(int x1, int y1, int x2, int y2);
};

