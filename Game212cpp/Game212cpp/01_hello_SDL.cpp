/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, int w, int h);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Scene textures
LTexture gFoxTexture;
LTexture gNatureBackgroundTexture;

//The music that will be played
Mix_Music *gMusic = nullptr;


LTexture::LTexture()
{
	//Initialize
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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
	mTexture = newTexture;
	return mTexture != nullptr;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, int w, int h)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, w, h };
	SDL_RenderCopy(gRenderer, mTexture, nullptr, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Fox texture
	if (!gFoxTexture.loadFromFile("Forest_Spirits_Image/foxcartoon.png"))
	{
		printf("Failed to load Fox texture image!\n");
		success = false;
	}

	//Load background texture
	if (!gNatureBackgroundTexture.loadFromFile("Background_Image/nature_background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	//Load music
	gMusic = Mix_LoadMUS("Sound_effects_and_music/beat.wav");
	if (gMusic == nullptr)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	return success;
}

void close()
{
	//Free loaded images
	gFoxTexture.free();
	gNatureBackgroundTexture.free();

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	int foxPosX = 200;
	int foxPosY = 300;
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Testing music key press
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_9:
							//If there is no music playing
							if (Mix_PlayingMusic()== 0)
							{
								//Play the music
								Mix_PlayMusic(gMusic, -1);
							}
							//If the music is being played
							else
							{
								//If the music is paused
								if (Mix_PausedMusic()==1)
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//if the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;

						case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;
						}
					}
					// Handle mouse events
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						if (mouseX >= foxPosX && mouseX < foxPosX + gFoxTexture.getWidth() && mouseY >= foxPosX && mouseY < foxPosY + gFoxTexture.getHeight())
						{
							printf("The fox image has been clicked down!\n");
						}
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						if (mouseX >= foxPosX && mouseX < foxPosX + gFoxTexture.getWidth() &&
							mouseY >= foxPosY && mouseY < foxPosY + gFoxTexture.getHeight()) {
							printf("The fox image has been released!\n");
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background texture to screen
				gNatureBackgroundTexture.render(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				//Render Foo' to the screen
				gFoxTexture.render(foxPosX, foxPosY, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}