#include <SDL.h>
#include <stdio.h>
#include <string>

class KeyPresses04 {
  enum KeyPressSurfaces
  {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
  };

public:
  KeyPresses04();
  int Run();

private:
  //Starts up SDL and creates a window
  bool init();

  //Loads media
  bool loadMedia();

  //Process input and events
  void processEvents();

  SDL_Surface* loadSurface(std::string path);

  //Frees media and shuts down SDL
  void close();

  const static int SCREEN_WIDTH = 640;
  const static int SCREEN_HEIGHT = 480;

  bool isRunning = true;
  SDL_Window* _window = NULL;
  SDL_Surface* _screenSurface = NULL;

  //Current displayed image
  SDL_Surface* _currentSurface = NULL;

  //The images that correspond to a keypress
  SDL_Surface* _keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
};