#include "sandSim.h"
#include <iostream>

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
    _scale = 3;

    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    _window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * _scale, SCREEN_HEIGHT * _scale, SDL_WINDOW_SHOWN);
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
                P_EMPTY,
            };
            _points1[y * SCREEN_WIDTH + x].isLiquidOrGas = true;
        }
    }

    //Set active buffers
    _particleGrid = _points1;

    return true;
}

void SandSim::render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

    //Clear screen
    SDL_RenderClear(_renderer);

    SDL_RenderSetScale(_renderer, _scale, _scale);

    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    {
        Particle particle = _particleGrid[i];
        if (!particle.hasUpdated) {
            continue;
        }

        SDL_SetRenderDrawColor(_renderer, particle.color.r, particle.color.g, particle.color.b, particle.color.a);
        SDL_RenderDrawPoint(_renderer, _particleGrid[i].p.x, _particleGrid[i].p.y);
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
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                _lDown = true;
                break;
            case SDL_BUTTON_RIGHT:
                _rDown = true;
                break;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
            switch (e.button.button) {
            case SDL_BUTTON_LEFT:
                _lDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                _rDown = false;
                break;
            }
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                _isRunning = false;
                break;
            case SDLK_SPACE:
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                _particleGrid[mouseY * SCREEN_WIDTH + mouseX].id = P_SAND;
                break;
            default:
                break;
            }
        }
    }

    if (_lDown || _rDown) {
        char type = _lDown ? P_SAND : P_WATER;
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        mouseX /= _scale;
        mouseY /= _scale;
        for (int x = -2; x < 3; x++) 
        {
            for (int y = -2; y < 3; y++) 
            {
                Particle* particle = &_particleGrid[(mouseY + y) * SCREEN_WIDTH + (mouseX + x)];
                particle->id = type;
                switch (type)
                {
                case P_SAND:
                    particle->color = { 0xE5, 0xDD, 0xD1, 0xFF };
                    particle->color.r += MathUtils::Rand(20) - 10;
                    particle->color.g += MathUtils::Rand(20) - 10;
                    particle->color.b += MathUtils::Rand(20) - 10;
                    particle->isLiquidOrGas = false;
                    break;
                case P_WATER:
                    particle->color = { 0x00, 0x9D, 0xDC, 0xDD };
                    particle->color.g += MathUtils::Rand(20) - 10;
                    particle->color.b += MathUtils::Rand(20) - 10;
                    particle->isLiquidOrGas = true;
                    break;
                }
            }
        }
        //_particleGrid[mouseY * SCREEN_WIDTH + mouseX].id = P_SAND;
    }
}

void SandSim::simulate()
{
    Uint32 ticks = SDL_GetTicks();
    int startX, startY, endX, endY, dirX, dirY;
    startY = SCREEN_HEIGHT - 1; endY = -1; dirY = -1;
    _simDir = rand() % 2 ? 1 : -1;

    for (int y = SCREEN_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            Particle* p = &_particleGrid[0];
            tryGetParticle(x, y, &p);
            p->hasUpdated = false;
        }
    }

    //for (int y = 0; y < SCREEN_HEIGHT; y++)
    for (int y = startY; y != endY; y += dirY)
    {
        if (_simLeft) {
            startX = 0; endX = SCREEN_WIDTH; dirX = 1;
        }
        else {
            startX = SCREEN_WIDTH - 1; endX = -1; dirX = -1;
        }
        _simLeft = !_simLeft;

        for (int x = startX; x != endX; x += dirX)
        {
            updateParticle(x, y);
        }
    }
}

void SandSim::updateParticle(int x, int y)
{
    Particle* p, * p2;
    tryGetParticle(x, y, &p);
    if (p->hasUpdated) {
        return;
    }

    bool didUpdate = false;
    switch (p->id)
    {
    case P_SAND:
        didUpdate = updateSand(x, y, &p2);
        break;
    case P_WATER:
        didUpdate = updateWater(x, y, &p2);
        break;
    default:
        return;
    }

    if (didUpdate) {
        swapParticles(p, p2);
        p2->hasUpdated = true;
        return;
    }
    p->hasUpdated = true;
}

bool SandSim::updateSand(int x, int y, Particle** outParticle)
{
    *outParticle = &_particleGrid[y * SCREEN_WIDTH + x];
    if (tryGetParticle(x, y + 1, outParticle) && (*outParticle)->isLiquidOrGas) return true;
    if (tryGetParticle(x + _simDir, y + 1, outParticle) && (*outParticle)->isLiquidOrGas) return true;
    if (tryGetParticle(x - _simDir, y + 1, outParticle) && (*outParticle)->isLiquidOrGas) return true;
    return false;
}

bool SandSim::updateWater(int x, int y, Particle** outParticle)
{
    *outParticle = &_particleGrid[y * SCREEN_WIDTH + x];
    if (tryGetParticle(x, y + 1, outParticle) && (*outParticle)->id == P_EMPTY) return true;
    if (tryGetParticle(x + _simDir, y + 1, outParticle) && (*outParticle)->id == P_EMPTY) return true;
    if (tryGetParticle(x - _simDir, y + 1, outParticle) && (*outParticle)->id == P_EMPTY) return true;
    if (tryGetParticle(x - _simDir, y, outParticle) && (*outParticle)->id == P_EMPTY) return true;
    if (tryGetParticle(x + _simDir, y, outParticle) && (*outParticle)->id == P_EMPTY) return true;
    return false;
}

void SandSim::swapParticles(Particle* p1, Particle* p2) {
    SDL_Point firstPoint = p1->p;
    SDL_Point secondPoint = p2->p;
    Particle temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    p1->p = firstPoint;
    p2->p = secondPoint;
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

void SandSim::clearBuffer(Particle* buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        buffer[i].id = P_EMPTY;
    }
}

bool SandSim::tryGetParticle(int x, int y, Particle** outParticle)
{
    if (x < 0 || y < 0 || x > (SCREEN_WIDTH - 1) || y > (SCREEN_HEIGHT - 1)) {
        return false;
    }
    *outParticle = &_particleGrid[y * SCREEN_WIDTH + x];
    return true;
}

int SandSim::getArrayPosition(int x, int y) {
    return y * SCREEN_WIDTH + x;
}
