#include <SDL.h>
#include <stdio.h>

class Image02 {
public:
  Image02();
  int Run();

private:
  //Starts up SDL and creates a window
  bool init();

  //Loads media
  bool loadMedia();

  //Frees media and shuts down SDL
  void close();

  SDL_Window* _window = NULL;
  SDL_Surface* _screenSurface = NULL;
  SDL_Surface* _helloWorld = NULL;

  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
};