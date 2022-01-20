#include "Dot.h"
#include "26_motion.h"
#include <iostream>

Dot::Dot()
{
    //Init offsets
    _posX = 0;
    _posY = 0;

    //Init velocity
    _velX = 0;
    _velY = 0;

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

void Dot::move()
{
    //Move the dot
    _posX += _velX;
    _posY += _velY;

    //If the dot moves too far, move it back
    if ((_posX < 0) || (_posX + DOT_WIDTH > Motion26::SCREEN_WIDTH)) {
        _posX -= _velX;
    }
    if ((_posY < 0) || (_posY + DOT_HEIGHT > Motion26::SCREEN_HEIGHT)) {
        _posY -= _velY;
    }
}

void Dot::render()
{
    _texture->render(_posX, _posY);
}
