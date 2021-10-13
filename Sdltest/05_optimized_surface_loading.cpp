#include "05_optimized_surface_loading.h"

SurfaceLoading05::SurfaceLoading05() { }

int SurfaceLoading05::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    _currentSurface = loadSurface("05/stretch.bmp");
    if (!_currentSurface) {
        printf("Failed to load stretch image");
        return -1;
    }

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    while (isRunning) {
        processEvents();
        SDL_BlitScaled(_currentSurface, NULL, _screenSurface, &stretchRect);
        SDL_UpdateWindowSurface(_window);
    }

    close();
    return 0;
}

bool SurfaceLoading05::init()
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    _window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (_window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Get window surface
    _screenSurface = SDL_GetWindowSurface(_window);
    return true;
}

void SurfaceLoading05::processEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }
}

SDL_Surface* SurfaceLoading05::loadSurface(std::string path)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface == NULL) {
        printf("Unable to load image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return optimizedSurface;
    }

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(surface, _screenSurface->format, 0);
    if (optimizedSurface == NULL) {
        printf("Unable to optimize image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return optimizedSurface;
    }
    //Free the old surface
    SDL_FreeSurface(surface);

    return optimizedSurface;
}

void SurfaceLoading05::close()
{
    //Deallocate surface
    SDL_FreeSurface(_currentSurface);
    _currentSurface = NULL;

    //Destroy window
    SDL_DestroyWindow(_window);
    _window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}