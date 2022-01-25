#include <SDL_events.h>
#include "lTexture.h"
#include "Utils.h"
#include <vector>

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

    Dot(int x, int y);

    ~Dot();

    //Sets the texture
    void setTexture(LTexture* texture);

    //Takes key presses and adjusts the dots velocity
    void handleEvent(SDL_Event& e);

    //Moves the dot
    void move(std::vector<SDL_Rect>& otherColliders);

    //Shows the dot on the screen
    void render();

    //Gets the collision boxes
    std::vector<SDL_Rect>& getColliders();

private:
    //The current X and Y offset of the dot
    int _posX, _posY;

    //The current velocity of the dot
    int _velX, _velY;

    //The dot's collider
    std::vector<SDL_Rect> _colliders;

    //Moves the collision boxes relative to the dot's offset
    void shiftColliders();

    LTexture* _texture;
};

#endif // !DOT
