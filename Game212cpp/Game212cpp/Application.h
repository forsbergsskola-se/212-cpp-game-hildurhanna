#pragma once

#include "Singleton.h"

#include <SDL.h>

class Application : public CSingleton<Application>
{
public:

	 Application();
	~Application();

	bool init();
	void run();
	void close();

	void handleEvents();
	void update();
	void render();

private:

	//The window we'll be rendering to
	SDL_Window* gWindow = nullptr;

	//The window renderer
	SDL_Renderer* gRenderer = nullptr;

};

