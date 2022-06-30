#include "LButton.h"

LButton::LButton() 
{
    _position.x = 0;
    _position.y = 0;

    _currentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
}

LButton::LButton(LTexture* texture)
{
    _position.x = 0;
    _position.y = 0;

    _currentSprite = LButtonSprite::BUTTON_SPRITE_MOUSE_OUT;
    _buttonSpriteSheetTexture = texture;

    for (int i = 0; i < LButtonSprite::BUTTON_SPRITE_TOTAL; i++)
    {
        _spriteClips[i] = {
            0,
            i * 200,
            BUTTON_WIDTH,
            BUTTON_HEIGHT
        };
    }
}

void LButton::setTexture(LTexture* texture) 
{
    _buttonSpriteSheetTexture = texture;

    for (int i = 0; i < LButtonSprite::BUTTON_SPRITE_TOTAL; i++)
    {
        _spriteClips[i] = {
            0,
            i * 200,
            BUTTON_WIDTH,
            BUTTON_HEIGHT
        };
    }
}

void LButton::setPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
    //If mouse event happened
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < _position.x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > _position.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < _position.y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > _position.y + BUTTON_HEIGHT)
        {
            inside = false;
        }

        //Mouse is outside button
        if (!inside)
        {
            _currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                _currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                _currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                _currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

void LButton::render()
{
    //Show current button sprite
    _buttonSpriteSheetTexture->render(_position.x, _position.y, &_spriteClips[_currentSprite]);
}