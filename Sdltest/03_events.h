#include <SDL.h>
#include <stdio.h>

class Events03 {
public:
  Events03();
  int Run();

private:
  //Starts up SDL and creates a window
  bool init();

  //Loads media
  bool loadMedia();

  //Process input and events
  void processEvents();

  //Frees media and shuts down SDL
  void close();

  bool _isRunning = true;
  SDL_Window* _window = NULL;
  SDL_Surface* _screenSurface = NULL;
  SDL_Surface* _helloWorld = NULL;

  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
};