#include "08_primitives.h"

Primitives08::Primitives08() { }

int Primitives08::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
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
        _time = SDL_GetTicks() * 0.001f;
    }

    close();
    return 0;
}

bool Primitives08::init()
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
    SDL_SetRenderDrawColor(_renderer, 0x33, 0x33, 0x33, 0xFF);

    return true;
}

void Primitives08::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0x33, 0x33, 0x33, 0xff);
    SDL_RenderClear(_renderer);

    //Render red filled quad
    SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(_renderer, &fillRect);

    //Render green outlined quad
    SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
    SDL_SetRenderDrawColor(_renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(_renderer, &outlineRect);

    //Draw blue horizontal line
    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderDrawLine(_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0x00, 0xFF);
    for (int i = 0; i < SCREEN_HEIGHT; i += 3)
    {
        SDL_RenderDrawPoint(_renderer, SCREEN_WIDTH / 2 + sin(i * 0.1f + _time * 2) * 20, i);
    }

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Primitives08::processEvents()
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

void Primitives08::close()
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