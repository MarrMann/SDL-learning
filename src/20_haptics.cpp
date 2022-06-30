#include "20_haptics.h"

Haptics20::Haptics20() { }

int Haptics20::Run()
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

bool Haptics20::init()
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joysticks connected.\n");
    }
    else {
        //Load joystick
        _gameController = SDL_JoystickOpen(0);
        if (_gameController == NULL) {
            printf("Warning: Unable to open game controller. SDL Error: %s\n", SDL_GetError());
        }
        else {
            //Get controller haptic device
            _controllerHaptic = SDL_HapticOpenFromJoystick(_gameController);
            if (_controllerHaptic == NULL) {
                printf("Warning: Could not get controller haptic. SDL error: %s\n", SDL_GetError());
            }
            else {
                //Initialize rumble
                if (SDL_HapticRumbleInit(_controllerHaptic) < 0) {
                    printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
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

    _arrowTexture = new LTexture(_renderer);

    return true;
}

void Haptics20::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Calculate angle
    double joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

    //Correct angle
    if (xDir == 0 && yDir == 0)
    {
        joystickAngle = 0;
    }

    //Render texture
    _arrowTexture->render((SCREEN_WIDTH - _arrowTexture->getWidth()) / 2, (SCREEN_HEIGHT - _arrowTexture->getHeight()) / 2, NULL, joystickAngle);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Haptics20::processEvents()
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
        //Joystick button press
        else if (e.type == SDL_JOYBUTTONDOWN) {
            //Play rumble at 75% strength for 500 milliseconds
            if (SDL_HapticRumblePlay(_controllerHaptic, 0.75, 500) != 0) {
                printf("Warning: Unable to play rumble! %s\n", SDL_GetError());
            }
        }
    }
}

bool Haptics20::loadMedia()
{
    if (!_arrowTexture->loadFromFile("19/arrow.png")) {
        printf("Failed to load arrow texture\n");
        return false;
    }

    return true;
}

void Haptics20::close()
{
    //Deallocate textures
    _arrowTexture->free();

    //Close game controller
    SDL_JoystickClose(_gameController);
    SDL_HapticClose(_controllerHaptic);
    _gameController = NULL;

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}