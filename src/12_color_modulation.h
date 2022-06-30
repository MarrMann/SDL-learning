#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "lTexture.h"

class ColorModulation12 {

public:
    ColorModulation12();
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

    //Color modulation
    Uint8 _r = 255;
    Uint8 _g = 255;
    Uint8 _b = 255;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
    LTexture* _modTexture;
};