#include "04_key_presses.h"

KeyPresses04::KeyPresses04() { }

int KeyPresses04::Run()
{
  //Startup SDL and create window
  if (!init()) {
    printf("Failed to initialize.\n");
    return -1;
  }

  if (!loadMedia()) {
    printf("Failed to load media.\n");
    return -1;
  }

  _currentSurface = _keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
  
  while (isRunning) {
    processEvents();
    SDL_BlitSurface(_currentSurface, NULL, _screenSurface, NULL);
    SDL_UpdateWindowSurface(_window);
  }

  close();
  return 0;
}

bool KeyPresses04::init()
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
  return true;
}

bool KeyPresses04::loadMedia()
{
  //Load default surface
  _keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04/press.bmp");
  if (_keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
  {
    printf("Failed to load default image!\n");
    return false;
  }

  //Load up surface
  _keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04/up.bmp");
  if (_keyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
  {
    printf("Failed to load up image!\n");
    return false;
  }

  //Load down surface
  _keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04/down.bmp");
  if (_keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
  {
    printf("Failed to load down image!\n");
    return false;
  }

  //Load left surface
  _keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04/left.bmp");
  if (_keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
  {
    printf("Failed to load left image!\n");
    return false;
  }

  //Load right surface
  _keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04/right.bmp");
  if (_keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
  {
    printf("Failed to load right image!\n");
    return false;
  }

  return true;
}

void KeyPresses04::processEvents()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      isRunning = false;
    }
    else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        _currentSurface = _keyPressSurfaces[KEY_PRESS_SURFACE_UP];
        break;
      case SDLK_DOWN:
        _currentSurface = _keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
        break;
      case SDLK_LEFT:
        _currentSurface = _keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
        break;
      case SDLK_RIGHT:
        _currentSurface = _keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
        break;
      case SDLK_ESCAPE:
        isRunning = false;
        break;
      default:
        break;
      }
    }
  }
}

SDL_Surface* KeyPresses04::loadSurface(std::string path)
{
  //Load image at specified path
  SDL_Surface* surface = SDL_LoadBMP(path.c_str());
  if (surface == NULL) {
    printf("Unable to load image %s. SDL error: %s\n", path.c_str(), SDL_GetError());
  }
  return surface;
}

void KeyPresses04::close()
{
  //Deallocate surface
  SDL_FreeSurface(_currentSurface);
  _currentSurface = NULL;

  //Destroy window
  SDL_DestroyWindow(_window);
  _window = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}