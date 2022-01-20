#include <SDL_events.h>
#include "lTexture.h"

#ifndef DOT
#define DOT

class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int MAX_VEL = 1;

    //Initializes the variables
    Dot();

    ~Dot();

    //Sets the texture
    void setTexture(LTexture* texture);

    //Takes key presses and adjusts the dots velocity
    void handleEvent(SDL_Event& e);

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render();

private:
    //The current X and Y offset of the dot
    int _posX, _posY;

    //The current velocity of the dot
    int _velX, _velY;

    LTexture* _texture;
};

#endif // !DOT
