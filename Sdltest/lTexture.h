#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

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

    //Creates image from font string
    bool loadFromRenderedText(std::string path, std::string textureText, SDL_Color textColor);

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 r, Uint8 g, Uint8 b);

    //Set blending mode
    void setBlendMode(SDL_BlendMode blendMode);

    //Set alpha modulation (transparency)
    void setAlpha(Uint8 a);

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* _texture;
    SDL_Renderer* _renderer = NULL;
    TTF_Font* _font = NULL;

    //Image dimensions
    int _width;
    int _height;
};