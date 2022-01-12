#include "22_timing.h"

Timing22::Timing22() { }

int Timing22::Run()
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

bool Timing22::init()
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

    _promptTexture = new LTexture(_renderer);
    _timeTexture = new LTexture(_renderer);

    return true;
}

void Timing22::render()
{
    //Prepare time text
    _timeText.str("");
    _timeText << "Milliseconds since start time " << SDL_GetTicks() - _startTime;

    //Render text
    if (!_timeTexture->loadFromRenderedText(_timeText.str().c_str(), _textColor)) {
        printf("Unable to render time texture.\n");
    }

    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render texture
    _promptTexture->render((SCREEN_WIDTH - _promptTexture->getWidth()) / 2, 0);
    _timeTexture->render((SCREEN_WIDTH - _promptTexture->getWidth()) / 2, (SCREEN_HEIGHT - _promptTexture->getHeight()) / 2);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Timing22::processEvents()
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
            case SDLK_RETURN:
                _startTime = SDL_GetTicks();
                break;
            default:
                break;
            }
        }
    }
}

bool Timing22::loadMedia()
{
    SDL_Color textColor = { 0, 0, 0, 255 };

    if (!_promptTexture->loadFromRenderedText("22/lazy.ttf", "Press Enter to Reset Start Time.", textColor)) {
        printf("Failed to render prompt texture\n");
        return false;
    }

    if (!_timeTexture->loadFromRenderedText("22/lazy.ttf", "0", textColor)) {
        printf("Failed to render time texture\n");
        return false;
    }

    return true;
}

void Timing22::close()
{
    //Deallocate textures
    _promptTexture->free();
    _timeTexture->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}