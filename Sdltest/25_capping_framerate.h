#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "lTexture.h"
#include "LButton.h"
#include "LTimer.h"

class CappingFramerate25 {

public:
    CappingFramerate25();
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
    const static int SCREEN_FPS = 144;
    const static int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

    //Needed for loop
    bool _isRunning = true;

    //Rendering targets
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
    LTexture* _fpsTexture;
    SDL_Color _textColor = { 0, 0, 0, 255 };
    LTimer _fpsTimer;
    LTimer _capTimer;
    int _countedFrames = 0;
    std::stringstream _timeText;
};