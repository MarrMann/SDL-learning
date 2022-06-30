#include <SDL.h>
#include <stdio.h>
#include <string>

class SurfaceLoading05 {

public:
    SurfaceLoading05();
    int Run();

private:
    //Starts up SDL and creates a window
    bool init();

    //Process input and events
    void processEvents();

    SDL_Surface* loadSurface(std::string path);

    //Frees media and shuts down SDL
    void close();

    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;

    bool _isRunning = true;
    SDL_Window* _window = NULL;
    SDL_Surface* _screenSurface = NULL;

    //Current displayed image
    SDL_Surface* _currentSurface = NULL;
};