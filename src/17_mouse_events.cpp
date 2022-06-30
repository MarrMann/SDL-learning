#include "17_mouse_events.h"

MouseEvents17::MouseEvents17() { }

int MouseEvents17::Run()
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

bool MouseEvents17::init()
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

    _buttonTexture = new LTexture(_renderer);
    
    _buttons = new LButton[4];
    for (int i = 0; i < LButton::TOTAL_BUTTONS; i++)
    {
        _buttons[i] = *new LButton(_buttonTexture);
    }

    _buttons[0].setPosition(0, 0);
    _buttons[1].setPosition(SCREEN_WIDTH - LButton::BUTTON_WIDTH, 0);
    _buttons[2].setPosition(0, SCREEN_HEIGHT - LButton::BUTTON_HEIGHT);
    _buttons[3].setPosition(SCREEN_WIDTH - LButton::BUTTON_WIDTH, SCREEN_HEIGHT - LButton::BUTTON_HEIGHT);

    return true;
}

void MouseEvents17::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render text
    for (int i = 0; i < LButton::TOTAL_BUTTONS; i++)
    {
        _buttons[i].render();
    }

    //Update screen
    SDL_RenderPresent(_renderer);
}

void MouseEvents17::processEvents()
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
        for (int i = 0; i < LButton::TOTAL_BUTTONS; i++)
        {
            _buttons[i].handleEvent(&e);
        }
    }
}

bool MouseEvents17::loadMedia()
{
    //Load sprite sheet
    if (!_buttonTexture->loadFromFile("17/button.png")) {
        printf("Failed to render button texture\n");
        return false;
    }

    return true;
}

void MouseEvents17::close()
{
    //Deallocate textures
    _buttonTexture->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}