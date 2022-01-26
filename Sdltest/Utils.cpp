#include "Utils.h"
#include <iostream>

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

bool Utils::checkCollision(Circle& a, Circle& b)
{
    //Calculate total radius squared
    int totalRadiusSquared = a.r + b.r;
    totalRadiusSquared *= totalRadiusSquared;

    //If the distance between the centers of the circles is less than the sum of their radii
    if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) {
        //The circles have collided
        return true;
    }

    return false;
}

bool Utils::checkCollision(Circle& a, SDL_Rect& b)
{
    //Closest point on collision box
    int cX, cY;

    //Find closest x offset
    if (a.x < b.x) {
        cX = b.x;
    }
    else if (a.x > b.x + b.w) {
        cX = b.x + b.w;
    }
    else {
        cX = a.x;
    }

    //Find closest y offset
    if (a.y < b.y) {
        cY = b.y;
    }
    else if (a.y > b.y + b.h) {
        cY = b.y + b.h;
    }
    else {
        cY = a.y;
    }

    //If the closest point is inside the circle
    if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
        //The box and circle have collided
        return true;
    }

    return false;
}

double Utils::distanceSquared(int x1, int y1, int x2, int y2)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX * deltaX + deltaY * deltaY;
}
