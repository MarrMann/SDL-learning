#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>1

#ifndef LTEXTURE
#define LTEXTURE
#endif // !LTEXTURE

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

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool loadFromRenderedText(std::string path, std::string textureText, SDL_Color textColor);
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

    //Deallocates texture
    void free(bool freeFont = false);

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
#if defined(SDL_TTF_MAJOR_VERSION)
    TTF_Font* _font = NULL;
#endif

    //Image dimensions
    int _width;
    int _height;
};