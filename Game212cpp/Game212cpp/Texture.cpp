#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::loadFromFile(std::string path)
{
    return false;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    return false;
}

void Texture::free()
{
}

void Texture::render(int x, int y, int w, int h)
{
}

int Texture::getWidth()
{
    return 0;
}

int Texture::getHeight()
{
    return 0;
}
