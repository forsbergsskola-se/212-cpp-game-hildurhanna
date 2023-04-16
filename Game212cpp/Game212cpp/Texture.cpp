#include "Texture.h"

#include "Application.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>


Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	auto newTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>{ nullptr, &SDL_DestroyTexture };

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture.reset(SDL_CreateTextureFromSurface(Application::GetInstance().GetRenderer(), loadedSurface));

		if (newTexture == nullptr)
		{
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
			
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = std::move(newTexture);
	return mTexture != nullptr;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(Application::GetInstance().GetFont(), textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		std::cout << "Unable to render text surface! SDL_image Error: " << TTF_GetError() << std::endl;
		//printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture.reset(SDL_CreateTextureFromSurface(Application::GetInstance().GetRenderer(), textSurface));
		if (mTexture == nullptr)
		{
			std::cout << "Unable to create texture from rendered text!! SDL_image Error: " << SDL_GetError() << std::endl;
			
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != nullptr;
}

void Texture::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture.get());
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::render(int x, int y, int w, int h)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Checks the rendering dimensions
	if (w != -1 && h != -1)
	{
		renderQuad.w = w;
		renderQuad.h = h;
	}

	SDL_RenderCopy(Application::GetInstance().GetRenderer(), mTexture.get(), nullptr, &renderQuad);

}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}
