#pragma once

#include <SDL.h>
#include <string>
#include <memory>

class Texture
{
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, int w, int h);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> mTexture{ nullptr, &SDL_DestroyTexture };


	//Image dimensions
	int mWidth = 0;
	int mHeight = 0;
};

