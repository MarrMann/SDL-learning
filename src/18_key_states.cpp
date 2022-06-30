#include "18_key_states.h"

KeyStates18::KeyStates18() { }

int KeyStates18::Run()
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

bool KeyStates18::init()
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

    _leftTexture = new LTexture(_renderer);
    _rightTexture = new LTexture(_renderer);
    _upTexture = new LTexture(_renderer);
    _downTexture = new LTexture(_renderer);
    _defaultTexture = new LTexture(_renderer);
    _activeTexture = _defaultTexture;

    return true;
}

void KeyStates18::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render texture
    _activeTexture->render(0, 0);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void KeyStates18::processEvents()
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

    //Set texture based on current keystate
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP]) {
        _activeTexture = _upTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
        _activeTexture = _downTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
        _activeTexture = _leftTexture;
    }
    else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
        _activeTexture = _rightTexture;
    }
    else {
        _activeTexture = _defaultTexture;
    }
}

bool KeyStates18::loadMedia()
{
    if (!_leftTexture->loadFromFile("18/left.png")) {
        printf("Failed to load left texture\n");
        return false;
    }
    if (!_rightTexture->loadFromFile("18/right.png")) {
        printf("Failed to load right texture\n");
        return false;
    }
    if (!_upTexture->loadFromFile("18/up.png")) {
        printf("Failed to load up texture\n");
        return false;
    }
    if (!_downTexture->loadFromFile("18/down.png")) {
        printf("Failed to load down texture\n");
        return false;
    }
    if (!_defaultTexture->loadFromFile("18/press.png")) {
        printf("Failed to load deafault texture\n");
        return false;
    }

    return true;
}

void KeyStates18::close()
{
    //Deallocate textures
    _leftTexture->free();
    _rightTexture->free();
    _downTexture->free();
    _upTexture->free();
    _defaultTexture->free();
    _activeTexture->free();

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}