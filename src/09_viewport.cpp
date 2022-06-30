#include "09_viewport.h"

Viewport09::Viewport09() { }

int Viewport09::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    _currentTexture = loadTexture("09/viewport.png");
    if (!_currentTexture) {
        printf("Failed to load texture!\n");
        return -1;
    }

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    while (_isRunning) {
        processEvents();
        render();
    }

    close();
    return 0;
}

bool Viewport09::init()
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

    //Create renderer
    _renderer = SDL_CreateRenderer(_window, -0, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void Viewport09::render()
{
    //Clear screen
    SDL_RenderClear(_renderer);

    //TopLeft viewport
    SDL_Rect topLeftViewport = { 0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_RenderSetViewport(_renderer, &topLeftViewport);

    //Render texture to screen
    SDL_RenderCopy(_renderer, _currentTexture, NULL, NULL);

    //TopRight viewport
    SDL_Rect topRightViewport = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_RenderSetViewport(_renderer, &topRightViewport);

    //Render texture to screen
    SDL_RenderCopy(_renderer, _currentTexture, NULL, NULL);

    //Bottom viewport
    SDL_Rect bottomViewport = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
    SDL_RenderSetViewport(_renderer, &bottomViewport);

    //Render texture to screen
    SDL_RenderCopy(_renderer, _currentTexture, NULL, NULL);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Viewport09::processEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            _isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                _isRunning = false;
                break;
            default:
                break;
            }
        }
    }
}

SDL_Texture* Viewport09::loadTexture(std::string path)
{
    //The final optimized image
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        printf("Unable to load image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return newTexture;
    }

    //Convert surface to screen format
    newTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (newTexture == NULL) {
        printf("Unable to optimize image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return newTexture;
    }
    //Free the old surface
    SDL_FreeSurface(surface);

    return newTexture;
}

void Viewport09::close()
{
    //Deallocate surface
    SDL_DestroyTexture(_currentTexture);
    _currentTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}