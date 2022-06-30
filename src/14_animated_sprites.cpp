#include "14_animated_sprites.h"

AnimatedSprites14::AnimatedSprites14() { }

int AnimatedSprites14::Run()
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

bool AnimatedSprites14::init()
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

    _spriteSheet = new LTexture(_renderer);

    return true;
}

void AnimatedSprites14::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render animated sprite
    SDL_Rect* currentClip = &_spriteClips[_spriteFrame / WALKING_ANIMATION_FRAMES];
    _spriteSheet->render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

    //Update screen
    SDL_RenderPresent(_renderer);

    //Increase frames
    _spriteFrame++;
    if (_spriteFrame / WALKING_ANIMATION_FRAMES >= WALKING_ANIMATION_FRAMES) {
        _spriteFrame = 0;
    }
}

void AnimatedSprites14::processEvents()
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

bool AnimatedSprites14::loadMedia()
{
    //Load sprite sheet
    if (!_spriteSheet->loadFromFile("14/foo.png")) {
        printf("Failed to load modulated texture");
        return false;
    }
    _spriteClips[0] = { 
        0,
        0, 
        64, 
        205 
    };
    _spriteClips[1] = { 
        64,
        0,
        64,
        205
    };
    _spriteClips[2] = { 
        128,
        0,
        64,
        205
    };
    _spriteClips[3] = { 
        196,
        0,
        64,
        205
    };

    return true;
}

void AnimatedSprites14::close()
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