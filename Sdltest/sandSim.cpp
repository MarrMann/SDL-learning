#include "sandSim.h"

SandSim::SandSim() { }

int SandSim::Run()
{
    //Startup SDL and create window
    if (!init()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    while (_isRunning) {
        processEvents();
        simulate();
        render();
    }

    close();
    return 0;
}

bool SandSim::init()
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

    //Create renderer
    _renderer = SDL_CreateRenderer(_window, -0, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Create pixel array
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            _points1[y * SCREEN_WIDTH + x] = {
                {x, y},
                0
            };
            _points2[y * SCREEN_WIDTH + x] = {
                {x, y},
                0
            };
        }
    }

    //Set active buffers
    _activePointBuffer = _points1;
    _backPointBuffer = _points2;

    return true;
}

void SandSim::render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

    //Clear screen
    SDL_RenderClear(_renderer);

    SDL_SetRenderDrawColor(_renderer, 0xE5, 0xDD, 0xD1, 0xFF);
    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    {
        if (_activePointBuffer[i].state) 
        {
            SDL_RenderDrawPoint(_renderer, _activePointBuffer[i].p.x, _activePointBuffer[i].p.y);
        }
    }

    SDL_RenderPresent(_renderer);
}

void SandSim::processEvents()
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
            case SDLK_SPACE:
                for (int x = -5; x < 5; x++)
                {
                    for (int y = -5; y < 5; y++)
                    {
                        _activePointBuffer[(SCREEN_HEIGHT / 2 + y) * SCREEN_WIDTH + (SCREEN_WIDTH / 2 + x)].state = 1;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}

void SandSim::simulate()
{
    int count = 0;
    //for (int y = 0; y < SCREEN_HEIGHT; y++)
    for (int y = SCREEN_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (_activePointBuffer[y * SCREEN_WIDTH + x].state == 1) {
                count++;
                if (y < SCREEN_HEIGHT - 1)
                {
                    if (_activePointBuffer[(y + 1) * SCREEN_WIDTH + x].state != 1) 
                    {
                        _activePointBuffer[y * SCREEN_WIDTH + x].state= 0;
                        _activePointBuffer[(y + 1) * SCREEN_WIDTH + x].state = 1;
                        continue;
                    }
                    
                    if (rand() % 2)
                    {
                        if (checkRight(_activePointBuffer, x, y))
                        {
                            checkLeft(_activePointBuffer, x, y);
                        }
                    }
                    else
                    {
                        if (!checkLeft(_activePointBuffer, x, y))
                        {
                            checkRight(_activePointBuffer, x, y);
                        }
                    }
                }
            }
        }
    }
}

bool SandSim::checkLeft(Point* buffer, int x, int y)
{
    if (x > 0 && buffer[(y + 1) * SCREEN_WIDTH + x - 1].state != 1) {
        buffer[y * SCREEN_WIDTH + x].state = 0;
        buffer[(y + 1) * SCREEN_WIDTH + x - 1].state = 1;
        return true;
    }
    return false;
}

bool SandSim::checkRight(Point* buffer, int x, int y)
{
    if (x < SCREEN_WIDTH - 1 && buffer[(y + 1) * SCREEN_WIDTH + x + 1].state != 1) {
        buffer[y * SCREEN_WIDTH + x].state = 0;
        buffer[(y + 1) * SCREEN_WIDTH + x + 1].state = 1;
        return true;
    }
    return false;
}

void SandSim::close()
{
    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void SandSim::swapPointBuffer()
{
    if (_isBackBufferActive) {
        _activePointBuffer = _points1;
        _backPointBuffer = _points2;
    }
    else {
        _activePointBuffer = _points2;
        _backPointBuffer = _points1;
    }
    clearBuffer(_backPointBuffer, SCREEN_WIDTH * SCREEN_HEIGHT);
    _isBackBufferActive = !_isBackBufferActive;
}

void SandSim::clearBuffer(Point* buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[i].state = 0;
    }
}