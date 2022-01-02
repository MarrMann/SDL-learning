#include "13_alpha_blending.h"

AlphaBlending13::AlphaBlending13() { }

int AlphaBlending13::Run()
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

bool AlphaBlending13::init()
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

    _modTexture = new LTexture(_renderer);
    _bgTexture = new LTexture(_renderer);

    return true;
}

void AlphaBlending13::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render bg texture
    _bgTexture->render(0, 0);

    //Render modulated texture
    _modTexture->setAlpha(_a);
    _modTexture->render(0, 0);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void AlphaBlending13::processEvents()
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
            case SDLK_w:
                if (_a + 32 > 255) {
                    _a = 255;
                    break;
                }
                _a += 32;
                break;
            case SDLK_s:
                if (_a - 32 < 0) {
                    _a = 0;
                    break;
                }
                _a -= 32;
                break;
            default:
                break;
            }
        }
    }
}

bool AlphaBlending13::loadMedia()
{
    //Load sprite sheet
    if (!_modTexture->loadFromFile("13/fadeout.png")) {
        printf("Failed to load modulated texture");
        return false;
    }
    _modTexture->setBlendMode(SDL_BLENDMODE_BLEND);

    if (!_bgTexture->loadFromFile("13/fadein.png")) {
        printf("Failed to load background");
        return false;
    }

    return true;
}

void AlphaBlending13::close()
{
    //Deallocate textures
    _modTexture->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}