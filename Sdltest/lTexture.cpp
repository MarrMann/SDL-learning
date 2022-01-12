#include "lTexture.h"

LTexture::LTexture(SDL_Renderer* renderer)
{
	//Initialize
	_renderer = renderer;
	_texture = NULL;
	_width = 0;
	_height = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free(true);
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	_texture = newTexture;
	return _texture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string path, std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free(true);

	_font = TTF_OpenFont(path.c_str(), 28);
	if (_font == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	return loadFromRenderedText(textureText, textColor);
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	if (_font == NULL) {
		printf("Cannot render a texture with no font.\n");
		return false;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	//Create texture from surface pixels
	_texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	if (_texture == NULL)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Get image dimensions
	_width = textSurface->w;
	_height = textSurface->h;

	//Get rid of old surface
	SDL_FreeSurface(textSurface);

	//Return success
	return _texture != NULL;
}
#endif

void LTexture::free(bool freeFont)
{
	//Free texture if it exists
	if (_texture != NULL)
	{
		SDL_DestroyTexture(_texture);
		_texture = NULL;
	}

#if defined(SDL_TTF_MAJOR_VERSION)
	if (_font != NULL && freeFont) {
		TTF_CloseFont(_font);
		_font = NULL;
	}
#endif

	_width = 0;
	_height = 0;
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(_texture, r, g, b);
}

void LTexture::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(_texture, blendMode);
}

void LTexture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(_texture, a);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, _width, _height };

	//Set clip dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(_renderer, _texture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return _width;
}

int LTexture::getHeight()
{
	return _height;
}
