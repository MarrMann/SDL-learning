#include "11_clip_rendering.h"

ClipRendering11::ClipRendering11() { }

int ClipRendering11::Run()
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

bool ClipRendering11::init()
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

    _spriteSheet = new LTexture(_renderer);

    return true;
}

void ClipRendering11::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render top left sprite
    _spriteSheet->render(0, 0, &_spriteClips[0]);

    //Render top right sprite
    _spriteSheet->render(SCREEN_WIDTH - _spriteClips[1].w, 0, &_spriteClips[1]);

    //Render bottom left sprite
    _spriteSheet->render(0, SCREEN_HEIGHT - _spriteClips[2].h, &_spriteClips[2]);

    //Render bottom right sprite
    _spriteSheet->render(SCREEN_WIDTH - _spriteClips[3].w, SCREEN_HEIGHT - _spriteClips[3].h, &_spriteClips[3]);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void ClipRendering11::processEvents()
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

bool ClipRendering11::loadMedia()
{
    //Load sprite sheet
    if (!_spriteSheet->loadFromFile("11/dots.png")) {
        printf("Failed to load sprite sheet texture");
        return false;
    }

    //Top left sprite
    _spriteClips[0] = {
        0, 0, 100, 100
    };

    //Top right sprite
    _spriteClips[1] = {
        100, 0, 100, 100
    };

    //Bottom left sprite
    _spriteClips[2] = {
        0, 100, 100, 100
    };

    //Bottom right sprite
    _spriteClips[3] = {
        100, 100, 100, 100
    };

    return true;
}

void ClipRendering11::close()
{
    //Deallocate textures
    _spriteSheet->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}