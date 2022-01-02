#include <string>
#include <SDL.h>

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture(SDL_Renderer* renderer);

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

    //Deallocates texture
    void free();

    void setColor(Uint8 r, Uint8 g, Uint8 b);

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* _texture;
    SDL_Renderer* _renderer = NULL;

    //Image dimensions
    int _width;
    int _height;
};