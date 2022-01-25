#include "Utils.h"

bool Utils::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
    //Check collision between all rects
    for (SDL_Rect& rectA : a) {
        for (SDL_Rect& rectB : b) {
            if (checkCollision(rectA, rectB)) {
                return true;
            }
        }
    }
    return false;
}

bool Utils::checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sizes of the rects
    int leftA, leftB;
    int rightA, rightB;
    int bottomA, bottomB;
    int topA, topB;

    //Calculate sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides of A are outside B
    if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false) {
        return true;
    }
    return false;
}
