#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include "lTexture.h"
#include "LButton.h"

class Haptics20 {

public:
    Haptics20();
    int Run();

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

    //Windows size
    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;
    const static int JOYSTICK_DEADZONE = 8000;

    //Needed for loop
    bool _isRunning = true;

    //Rendering targets
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Controllers
    SDL_Joystick* _gameController = NULL;
    SDL_Haptic* _controllerHaptic = NULL;
    int xDir = 0;
    int yDir = 0;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
    LTexture* _arrowTexture;
};