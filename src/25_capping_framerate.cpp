#include "25_capping_framerate.h"

CappingFramerate25::CappingFramerate25() {
    _countedFrames = 0;
}

int CappingFramerate25::Run()
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

    _fpsTimer.start();

    while (_isRunning) {
        _capTimer.start();
        processEvents();
        render();
    }

    close();
    return 0;
}

bool CappingFramerate25::init()
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
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    _fpsTexture = new LTexture(_renderer);

    return true;
}

void CappingFramerate25::render()
{
    //Calculate and correct fps
    float avgFps = _countedFrames / (_fpsTimer.getTicks() / 1000.f);
    if (avgFps > 2000000) {
        avgFps = 0;
    }

    //Prepare time text
    _timeText.str("");
    _timeText << "Average FPS (capped): " << avgFps;

    //Render text
    if (!_fpsTexture->loadFromRenderedText(_timeText.str().c_str(), _textColor)) {
        printf("Unable to render time texture.\n");
    }

    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render texture
    _fpsTexture->render((SCREEN_WIDTH - _fpsTexture->getWidth()) / 2, (SCREEN_HEIGHT - _fpsTexture->getHeight()) / 2);

    //Update screen
    SDL_RenderPresent(_renderer);
    _countedFrames++;

    //If frame finished early
    int frameTicks = _capTimer.getTicks();
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        //Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

void CappingFramerate25::processEvents()
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
            case SDLK_s:
                if (_fpsTimer.isStarted()) {
                    _fpsTimer.stop();
                }
                else {
                    _fpsTimer.start();
                }
                break;
            case SDLK_p:
                if (_fpsTimer.isPaused()) {
                    _fpsTimer.unpause();
                }
                else {
                    _fpsTimer.pause();
                }
                break;
            default:
                break;
            }
        }
    }
}

bool CappingFramerate25::loadMedia()
{
    SDL_Color textColor = { 0, 0, 0, 255 };

    if (!_fpsTexture->loadFromRenderedText("23/lazy.ttf", "0", textColor)) {
        printf("Failed to render prompt texture\n");
        return false;
    }

    return true;
}

void CappingFramerate25::close()
{
    //Deallocate textures
    _fpsTexture->free();

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