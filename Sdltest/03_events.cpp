#include "03_events.h"

Events03::Events03() { }

int Events03::Run()
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

  SDL_BlitSurface(_helloWorld, NULL, _screenSurface, NULL);
  SDL_UpdateWindowSurface(_window);
  while (_isRunning) {
    processEvents();
  }

  close();
  return 0;
}

bool Events03::init()
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

bool Events03::loadMedia()
{
  //Load the image
  _helloWorld = SDL_LoadBMP("02/hello_world.bmp");
  if (_helloWorld == NULL) {
    printf("Unable to load image %s! SDL error: %s\n", "02/hello_world.bmp", SDL_GetError());
    return false;
  }

  return true;;
}

void Events03::processEvents()
{
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      _isRunning = false;
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
      _isRunning = false;
    }
  }
}

void Events03::close()
{
  //Deallocate surface
  SDL_FreeSurface(_helloWorld);
  _helloWorld = NULL;

  //Destroy window
  SDL_DestroyWindow(_window);
  _window = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}