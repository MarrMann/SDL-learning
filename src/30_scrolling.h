#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "lTexture.h"
#include "Dot.h"

class Scrolling30 {

public:
    Scrolling30();
    int Run();

    //Windows size
    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;

    //Level size
    const static int LEVEL_WIDTH = 1280;
    const static int LEVEL_HEIGHT = 960;

private:
    //Starts up SDL and creates a window
    bool init();

    //Render content
    void render();

    //Process input and events
    void processEvents();

    //Load required media
    bool loadMedia();

    //Frees media and shuts down SDL
    void close();

    //Needed for loop
    bool _isRunning = true;

    //Objects
    Dot* _dot;

    //Camera area
    SDL_Rect _camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Textures
    LTexture* _dotTexture;
    LTexture* _bgTexture;

    //Rendering targets
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
};