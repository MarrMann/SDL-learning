#include "Dot.h"
#include "26_motion.h"
#include <iostream>

Dot::Dot() : Dot(0, 0) { }

Dot::Dot(int x, int y)
{
    //Init offsets
    _posX = x;
    _posY = y;

    //Init collider
    _collider.r = DOT_WIDTH / 2;

    //Init velocity
    _velX = 0;
    _velY = 0;

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

void Dot::move(SDL_Rect& square, Circle& circle)
{
    //Move the dot
    _posX += _velX;
    shiftColliders();

    //If the dot moves too far, move it back
    if ((_posX < 0) || (_posX + DOT_WIDTH > Motion26::SCREEN_WIDTH) || Utils::checkCollision(_collider, square) || Utils::checkCollision(_collider, circle)) {
        _posX -= _velX;
        shiftColliders();
    }

    _posY += _velY;
    shiftColliders();

    if ((_posY < 0) || (_posY + DOT_HEIGHT > Motion26::SCREEN_HEIGHT) || Utils::checkCollision(_collider, square) || Utils::checkCollision(_collider, circle)) {
        _posY -= _velY;
        shiftColliders();
    }
}

void Dot::render()
{
    _texture->render(_posX - _collider.r, _posY - _collider.r);
}

std::vector<SDL_Rect>& Dot::getColliders()
{
    return _colliders;
}

Circle& Dot::getCollider()
{
    return _collider;
}

void Dot::shiftColliders()
{
    _collider.x = _posX;
    _collider.y = _posY;
}
