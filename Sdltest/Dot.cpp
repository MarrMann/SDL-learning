#include "Dot.h"
#include "26_motion.h"
#include <iostream>

Dot::Dot() : Dot(0, 0) { }

Dot::Dot(int x, int y)
{
    //Init offsets
    _posX = x;
    _posY = y;

    //Init velocity
    _velX = 0;
    _velY = 0;

    //Create the necessary rects
    _colliders.resize(11);

    //Initialize the collision boxes' width and height
    _colliders[0].w = 6;
    _colliders[0].h = 1;

    _colliders[1].w = 10;
    _colliders[1].h = 1;

    _colliders[2].w = 14;
    _colliders[2].h = 1;

    _colliders[3].w = 16;
    _colliders[3].h = 2;

    _colliders[4].w = 18;
    _colliders[4].h = 2;

    _colliders[5].w = 20;
    _colliders[5].h = 6;

    _colliders[6].w = 18;
    _colliders[6].h = 2;

    _colliders[7].w = 16;
    _colliders[7].h = 2;

    _colliders[8].w = 14;
    _colliders[8].h = 1;

    _colliders[9].w = 10;
    _colliders[9].h = 1;

    _colliders[10].w = 6;
    _colliders[10].h = 1;

    //Initialize colliders relative to position
    shiftColliders();

    //Init texture
    _texture = NULL;
}

Dot::~Dot()
{
    _texture->free();
}

void Dot::setTexture(LTexture* texture)
{
    _texture = texture;
}

void Dot::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if (e.key.repeat == 0) {
        if (e.type == SDL_KEYDOWN) {
            std::cout << "Key down!\n";
            //Adjust velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT: _velX -= MAX_VEL; break;
            case SDLK_RIGHT: _velX += MAX_VEL; break;
            case SDLK_UP: _velY -= MAX_VEL; break;
            case SDLK_DOWN: _velY += MAX_VEL; break;
            default:
                break;
            }
        }
        else if (e.type == SDL_KEYUP) {
            std::cout << "Key up!\n";
            //Adjust velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT: _velX += MAX_VEL; break;
            case SDLK_RIGHT: _velX -= MAX_VEL; break;
            case SDLK_UP: _velY += MAX_VEL; break;
            case SDLK_DOWN: _velY -= MAX_VEL; break;
            default:
                break;
            }
        }
    }
}

void Dot::move(std::vector<SDL_Rect>& otherColliders)
{
    //Move the dot
    _posX += _velX;
    std::cout << _posX;
    shiftColliders();

    //If the dot moves too far, move it back
    if ((_posX < 0) || (_posX + DOT_WIDTH > Motion26::SCREEN_WIDTH) || Utils::checkCollision(_colliders, otherColliders)) {
        _posX -= _velX;
        shiftColliders();
    }

    std::cout << " " << _posX << std::endl;

    _posY += _velY;
    shiftColliders();

    if ((_posY < 0) || (_posY + DOT_HEIGHT > Motion26::SCREEN_HEIGHT) || Utils::checkCollision(_colliders, otherColliders)) {
        _posY -= _velY;
        shiftColliders();
    }
}

void Dot::render()
{
    _texture->render(_posX, _posY);
}

std::vector<SDL_Rect>& Dot::getColliders()
{
    return _colliders;
}

void Dot::shiftColliders()
{
    //The row offset
    int r = 0;

    //Go through the dot's collision boxes
    for (int i = 0; i < _colliders.size(); i++) {
        //Center the collision box
        _colliders[i].x = _posX + (DOT_WIDTH - _colliders[i].w) / 2;

        //Set the collision box at its row offset
        _colliders[i].y = _posY + r;

        //Move the row offset down the height of the collision box
        r += _colliders[i].h;
    }
}
