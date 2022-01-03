#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include "lTexture.h"

class Rotation15 {

public:
    Rotation15();
    int Run();

private:
    //Starts up SDL and creates a window
    bool init();

    //Render content
    void render();

    //Process input and events
    void processEvents();

    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;

    bool _isRunning = true;
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
    LTexture* _arrow;
    double _degrees = 0;
    SDL_RendererFlip _flipType = SDL_FLIP_NONE;
};