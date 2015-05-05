#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

/**
@brief Creates a Texture for use with a renderer.
Creates a Texture from an image file, this can then be used with a renderer.
Reference ~ This is a modified version of my PGG Assignment 1 Texture class.
*/
class JAM_Texture
{
private:
	/**The Texture data*/
	SDL_Texture* textureData;
	/**The width of the Texture*/
	int textureWidth;
	/**The height of the Texture*/
	int textureHeight;

public:
	/**
	Constructs a Texture.
	Creates a Texture using an RGB value. This will create a 1x1 rectangle of that colour that can be scaled.
	@param std::string A pointer to the renderer.
	@param int The red value.
	@param int The green value.
	@param int The blue value
	*/
	JAM_Texture(SDL_Renderer* renderer, int r, int g, int b);

	/**
	Constructs a Texture
	Creates a Texture using an image location and a renderer. This is for use with SDL image.
	@param std::string The location of the image file.
	@param SDL_Renderer* The renderer.
	*/
	JAM_Texture(std::string fileLocation, SDL_Renderer* renderer);

	/**
	Constructs a Texture
	Creates a Texture using an image location and a renderer. The magenta pixels of this image can
	represent alpha if needed.
	@param std::string The location of the image file.
	@param SDL_Renderer* The renderer.
	@param bool If true any magenta pixels in the image will be converted to alpha
	*/
	JAM_Texture(std::string fileLocation, SDL_Renderer* renderer, bool magentaAlpha);

	/**
	Destructs the Texture deleting the Texture from memory.
	*/
	~JAM_Texture();

	/**
	Getter # Returns a pointer to the Texture
	Returns a pointer to the Texture data.
	*/
	SDL_Texture* getTexture();

	/**
	Getter # Returns textureWidth
	Returns the value of textureWidth.
	*/
	int getWidth();

	/**
	Getter # Returns textureHeight
	Returns the value of textureHeight.
	*/
	int getHeight();

	/**
	Pushes the image to the Renderer, to the XY Coordinates.
	@param SDL_Renderer* The renderer.
	@param int x coordinate of the image.
	@param int y coordinate of the image.
	*/
	void pushToScreen(SDL_Renderer* renderer, int x, int y);

	/**
	Pushes the image to the Renderer, to the XY Coordinates. This is scaled to the width and height
	inputed.
	@param SDL_Renderer* The renderer.
	@param int x coordinate of the image.
	@param int y coordinate of the image.
	@param int width of the scaled image.
	@param int height of the scaled image.
	*/
	void pushToScreen(SDL_Renderer* renderer, int x, int y, int width, int height);

	/**
	Pushes the image to the Renderer, to the XY Coordinates. Only displays the source rectangle inputed.
	@param SDL_Renderer* The renderer.
	@param int x coordinate of the image.
	@param int y coordinate of the image.
	@param int x coordinate of the source image.
	@param int y coordinate of the source image.
	@param int width of the source image.
	@param int height of the source image.
	*/
	void pushSpriteToScreen(SDL_Renderer* renderer, int x, int y, int srcX, int srcY, int srcWidth, int srcHeight);

	/**
	Pushes the image to the Renderer, to the XY Coordinates. Only displays the source rectangle inputed.
	This is scaled to the width and height inputed.
	@param SDL_Renderer* The renderer.
	@param int x coordinate of the image.
	@param int y coordinate of the image.
	@param int x coordinate of the source image.
	@param int y coordinate of the source image.
	@param int width of the source image.
	@param int height of the source image.
	@param int width of the scaled image.
	@param int height of the scaled image.
	*/
	void pushSpriteToScreen(SDL_Renderer* renderer, int x, int y, int srcX, int srcY, int srcWidth, int srcHeight, int width, int height);
};