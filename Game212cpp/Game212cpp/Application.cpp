#include "Application.h"

#include "MenuState.h"
#include "GameState.h"
#include "EndState.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Application::Application()
{
}

Application::~Application()
{
}

bool Application::init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	menuState = new MenuState;
	gameState = new GameState;
	endState = new EndState;
	currentState = menuState;

	return true;
}

void Application::run()
{
	//While application is running
	while (running)
	{
		handleEvents();
		update();
		render();
	}
}

void Application::close()
{
	delete endState;
	delete gameState;
	delete menuState;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Application::handleEvents()
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
			{
				running = false;

				break;
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				if (currentState)
					currentState->handleEvents();

				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				if (currentState)
					currentState->handleEvents();

				break;
			}

			default:
				break;
		}
	}
}

void Application::update()
{
	if (currentState)
		currentState->update();
}

void Application::render()
{
	if (currentState)
		currentState->render();
}
