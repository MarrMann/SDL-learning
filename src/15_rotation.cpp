#include "15_rotation.h"

Rotation15::Rotation15() { }

int Rotation15::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    if (!loadMedia()) {
        printf("Failed to load texture(s)!\n");
        return -1;
    }

    while (_isRunning) {
        processEvents();
        render();
    }

    close();
    return 0;
}

bool Rotation15::init()
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
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    _arrow = new LTexture(_renderer);

    return true;
}

void Rotation15::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render arrow
    _arrow->render((SCREEN_WIDTH - _arrow->getWidth()) / 2, (SCREEN_HEIGHT - _arrow->getHeight()) / 2, NULL, _degrees, NULL, _flipType);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Rotation15::processEvents()
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
            case SDLK_a:
                _degrees -= 60;
                break;
            case SDLK_d:
                _degrees += 60;
                break;
            case SDLK_q:
                _flipType = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_w:
                _flipType = SDL_FLIP_NONE;
                break;
            case SDLK_e:
                _flipType = SDL_FLIP_VERTICAL;
                break;
            default:
                break;
            }
        }
    }
}

bool Rotation15::loadMedia()
{
    //Load sprite sheet
    if (!_arrow->loadFromFile("15/arrow.png")) {
        printf("Failed to load arrow texture");
        return false;
    }

    return true;
}

void Rotation15::close()
{
    //Deallocate textures
    _arrow->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}