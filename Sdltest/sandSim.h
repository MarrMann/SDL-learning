#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <utility>
#include "mathUtils.h"

#define P_EMPTY 0
#define P_SAND 1
#define P_WATER 2

class SandSim {

    struct Particle {
        SDL_Point p;
        unsigned char id;
        SDL_Color color;
        SDL_Point velocity;
        float lifetime;
        bool hasUpdated;
        bool isLiquidOrGas;
    };

public:
    SandSim();
    int Run();

private:
    //Starts up SDL and creates a window
    bool init();

    //Render content
    void render();

    //Process input and events
    void processEvents();

    //Simulate pixels
    void simulate();

    void updateSand(int x, int y);
    void updateWater(int x, int y);
    void swapParticles(Particle *p1, Particle* p2);

    //Frees media and shuts down SDL
    void close();

    void clearBuffer(Particle* buffer, int size);

    Particle* getParticle(int x, int y);
    int getArrayPosition(int x, int y);

    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 320;

    bool _isRunning = true;
    bool _isBackBufferActive = false;
    SDL_Window* _window = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;

    //Array pointers
    Particle* _particleGrid;

    //Point array
    Particle _points1[SCREEN_HEIGHT * SCREEN_WIDTH];
    Particle _points2[SCREEN_HEIGHT * SCREEN_WIDTH];

    int _scale;
    char _simDir;
    bool _simLeft;
    bool _lDown;
    bool _rDown;
};