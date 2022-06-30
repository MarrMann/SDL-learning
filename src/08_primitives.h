#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Primitives08 {

public:
    Primitives08();
    int Run();

private:
    //Starts up SDL and creates a window
    bool init();

    //Render content
    void render();

    //Process input and events
    void processEvents();

    //Frees media and shuts down SDL
    void close();

    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;

    bool _isRunning = true;
    float _time = 0;
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;
    SDL_Texture* _currentTexture = NULL;
};