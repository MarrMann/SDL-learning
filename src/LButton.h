#include <SDL.h>

#ifndef LTEXTURE
#include "lTexture.h"
#endif // !LTEXTURE

#ifndef LBUTTON
#define LBUTTON
#endif // !LBUTTON


//The mouse button
class LButton
{
public:
    //Button constants
    const static int BUTTON_WIDTH = 300;
    const static int BUTTON_HEIGHT = 200;
    const static int TOTAL_BUTTONS = 4;

    //Initializes internal variables
    LButton();
    LButton(LTexture* texture);

    //Sets texture sheet
    void setTexture(LTexture* texture);

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    void handleEvent(SDL_Event* e);

    //Shows button sprite
    void render();

private:
    //Consts & enums
    enum LButtonSprite
    {
        BUTTON_SPRITE_MOUSE_OUT = 0,
        BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
        BUTTON_SPRITE_MOUSE_DOWN = 2,
        BUTTON_SPRITE_MOUSE_UP = 3,
        BUTTON_SPRITE_TOTAL = 4
    };

    //Top left position
    SDL_Point _position;

    //Currently used global sprite
    LButtonSprite _currentSprite;
    SDL_Rect _spriteClips[TOTAL_BUTTONS];
    LTexture* _buttonSpriteSheetTexture;
};