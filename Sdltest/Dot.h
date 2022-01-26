#include <SDL_events.h>
#include "lTexture.h"
#include "Utils.h"
#include <vector>

#ifndef DOT
#define DOT

struct Circle
{
    int x, y;
    int r;
};

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

    //Moves the dot and checks collision
    void move(SDL_Rect& square, Circle& circle);

    //Shows the dot on the screen
    void render();

    //Gets the collision boxes
    std::vector<SDL_Rect>& getColliders();

    //Gets collision circle
    Circle& getCollider();

private:
    //The current X and Y offset of the dot
    int _posX, _posY;

    //The current velocity of the dot
    int _velX, _velY;

    //The dot's collider
    std::vector<SDL_Rect> _colliders;

    //The dot's collision circle
    Circle _collider;

    //Moves the collision boxes relative to the dot's offset
    void shiftColliders();

    LTexture* _texture;
};

#endif // !DOT
