#include "07_textures.h"

Textures07::Textures07() { }

int Textures07::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    _currentTexture = loadTexture("07/texture.png");
    if (!_currentTexture) {
        printf("Failed to load texture!\n");
        return -1;
    }

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    while (_isRunning) {
        processEvents();
        render();
    }

    close();
    return 0;
}

bool Textures07::init()
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
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}

void Textures07::render()
{
    //Clear screen
    SDL_RenderClear(_renderer);

    //Render texture to screen
    SDL_RenderCopy(_renderer, _currentTexture, NULL, NULL);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void Textures07::processEvents()
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

SDL_Texture* Textures07::loadTexture(std::string path)
{
    //The final optimized image
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
        printf("Unable to load image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return newTexture;
    }

    //Convert surface to screen format
    newTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (newTexture == NULL) {
        printf("Unable to optimize image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
        return newTexture;
    }
    //Free the old surface
    SDL_FreeSurface(surface);

    return newTexture;
}

void Textures07::close()
{
    //Deallocate surface
    SDL_DestroyTexture(_currentTexture);
    _currentTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}