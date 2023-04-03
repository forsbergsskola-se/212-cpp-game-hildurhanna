/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(std::string path);
//The window we'll be rendering to
SDL_Window* gWindow{};
//The surface contained by the window
SDL_Surface* gScreenSurface{};
//The image we will load and show on screen
SDL_Surface* gHelloWorld{};
//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
//Current displayed image
SDL_Surface* gCurrentSurface = nullptr;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



int main( int argc, char* args[] )
{
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
			

			//Hack to get window to stay up
			SDL_Event e; bool quit = false;
			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			while (quit == false)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) )
				{
					//User request to quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						//Select surfaces based on the key press
						switch (e.key.keysym.sym)
						{
							case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

							default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				//Apply image
				SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	//Free resources and close SDL
	close();
	return 0;
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!gWindow)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("hello_world.bmp");
	if (!gHelloWorld)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
		success = false;
	}

	//Load default surface
	gKeyPressSurfaces [KEY_PRESS_SURFACE_DEFAULT] = loadSurface("img_for_press_test/press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("img_for_press_test/up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("img_for_press_test/down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("img_for_press_test/left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("img_for_press_test/right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	return success;
}

void close() {
	//Dealloacate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = nullptr;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//Quit SDL subsystem
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}


