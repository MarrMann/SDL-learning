#include "12_color_modulation.h"

ColorModulation12::ColorModulation12() { }

int ColorModulation12::Run()
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

bool ColorModulation12::init()
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

    return true;
}

void ColorModulation12::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render modulated texture
    _modTexture->setColor(_r, _g, _b);
    _modTexture->render(0, 0);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void ColorModulation12::processEvents()
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
            case SDLK_q:
                _r += 32;
                break;
            case SDLK_w:
                _g += 32;
                break;
            case SDLK_e:
                _b += 32;
                break;
            case SDLK_a:
                _r -= 32;
                break;
            case SDLK_s:
                _g -= 32;
                break;
            case SDLK_d:
                _b -= 32;
                break;
            default:
                break;
            }
        }
    }
}

bool ColorModulation12::loadMedia()
{
    //Load sprite sheet
    if (!_modTexture->loadFromFile("12/colors.png")) {
        printf("Failed to load sprite sheet texture");
        return false;
    }

    return true;
}

void ColorModulation12::close()
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