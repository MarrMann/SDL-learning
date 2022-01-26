#include "28_per_pixel_collision.h"

PerPixelCollision28::PerPixelCollision28() {
    _dot = new Dot(0, 0);
    _otherDot = new Dot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4);
    _dotTexture = NULL;
}

int PerPixelCollision28::Run()
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

bool PerPixelCollision28::init()
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        printf("TTF could not initialize! TTF error: %s\n", TTF_GetError());
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

    _dotTexture = new LTexture(_renderer);

    return true;
}

void PerPixelCollision28::render()
{
    //Move objets
    // Superceded by lesson 29
    //_dot->move(_otherDot->getColliders());

    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render texture
    _dot->render();
    _otherDot->render();

    //Update screen
    SDL_RenderPresent(_renderer);
}

void PerPixelCollision28::processEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        _dot->handleEvent(e);
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

bool PerPixelCollision28::loadMedia()
{
    if (!_dotTexture->loadFromFile("26/dot.bmp")) {
        printf("Failed to load dot texture\n");
        return false;
    }
    _dot->setTexture(_dotTexture);
    _otherDot->setTexture(_dotTexture);

    return true;
}

void PerPixelCollision28::close()
{
    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Delete objects
    delete _dot;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}