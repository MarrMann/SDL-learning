#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class SandSim {

    struct Point {
        SDL_Point p;
        int state = 0;
    };

public:
    SandSim();
    int Run();

private:
    //Starts up SDL and creates a window
    bool init();

    //Render content
    void render();

    //Process input and events
    void processEvents();

    //Simulate pixels
    void simulate();
    bool checkLeft(Point* buffer, int x, int y);
    bool checkRight(Point* buffer, int x, int y);

    //Frees media and shuts down SDL
    void close();

    //Swap buffer array;
    void swapPointBuffer();

    void clearBuffer(Point* buffer, int size);

    const static int SCREEN_WIDTH = 640;
    const static int SCREEN_HEIGHT = 480;

    bool _isRunning = true;
    bool _isBackBufferActive = false;
    SDL_Window* _window = NULL;

    //Current displayed image and renderer
    SDL_Renderer* _renderer = NULL;

    //Array pointers
    Point* _activePointBuffer;
    Point* _backPointBuffer;

    //Point array
    Point _points1[SCREEN_HEIGHT * SCREEN_WIDTH];
    Point _points2[SCREEN_HEIGHT * SCREEN_WIDTH];
};