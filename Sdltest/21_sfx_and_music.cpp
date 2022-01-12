#include "21_sfx_and_music.h"

SfxAndMusic21::SfxAndMusic21() { }

int SfxAndMusic21::Run()
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

bool SfxAndMusic21::init()
{
    //Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_Mixer could not initialize. SDL_Mixer error: %s\n", Mix_GetError());
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

    return true;
}

void SfxAndMusic21::render()
{
    //Clear screen
    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(_renderer);

    //Render texture
    _promptTexture->render(0, 0);

    //Update screen
    SDL_RenderPresent(_renderer);
}

void SfxAndMusic21::processEvents()
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
            case SDLK_1:
                Mix_PlayChannel(-1, _high, 0);
                break;
            case SDLK_2:
                Mix_PlayChannel(-1, _medium, 0);
                break;
            case SDLK_3:
                Mix_PlayChannel(-1, _low, 0);
                break;
            case SDLK_4:
                Mix_PlayChannel(-1, _scratch, 0);
                break;
            case SDLK_9:
                //If there's no music playing
                if (Mix_PlayingMusic() == 0) {
                    //Play the music
                    Mix_PlayMusic(_music, -1);
                }
                //If the music is being played
                else {
                    //If the music is paused
                    if (Mix_PausedMusic() == 1) {
                        //Resume the music
                        Mix_ResumeMusic();
                    }
                    //If the music is playing
                    else {
                        //Pause the music
                        Mix_PauseMusic();
                    }
                }
                break;
            case SDLK_0:
                //Stop the music
                Mix_HaltMusic();
                break;
            default:
                break;
            }
        }
    }
}

bool SfxAndMusic21::loadMedia()
{
    if (!_promptTexture->loadFromFile("21/prompt.png")) {
        printf("Failed to load prompt texture\n");
        return false;
    }

    //Load music
    _music = Mix_LoadMUS("21/beat.wav");
    if (_music == NULL) {
        printf("Failed to load music. Error: %s\n", Mix_GetError());
        return false;
    }

    //Load sfx
    _scratch = Mix_LoadWAV("21/scratch.wav");
    if (_scratch == NULL) {
        printf("Failed to load scratch sound effect. Error: %s\n", Mix_GetError());
        return false;
    }

    _low = Mix_LoadWAV("21/low.wav");
    if (_low == NULL) {
        printf("Failed to load low sound effect. Error: %s\n", Mix_GetError());
        return false;
    }

    _medium = Mix_LoadWAV("21/medium.wav");
    if (_medium == NULL) {
        printf("Failed to load medium sound effect. Error: %s\n", Mix_GetError());
        return false;
    }

    _high = Mix_LoadWAV("21/high.wav");
    if (_high == NULL) {
        printf("Failed to load high sound effect. Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void SfxAndMusic21::close()
{
    //Deallocate textures
    _promptTexture->free();

    //Free sfx
    Mix_FreeChunk(_scratch);
    _scratch = NULL;
    Mix_FreeChunk(_low);
    _low = NULL;
    Mix_FreeChunk(_medium);
    _medium = NULL;
    Mix_FreeChunk(_high);
    _high = NULL;

    //Free music
    Mix_FreeMusic(_music);
    _music = NULL;

    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}