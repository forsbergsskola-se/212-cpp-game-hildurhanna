#pragma once

#include "Singleton.h"
#include "State.h"

#include <SDL.h>
#include <SDL_ttf.h>

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

	void GenerateEndTexture(const float timer);

public:

	SDL_Renderer* GetRenderer() { return renderer; }

	TTF_Font* GetFont() { return font; }

	Texture& GetEndTexture() { return (Texture&)endTexture; }

	void SetState(State* newState) { currentState = newState; }

	State* GetMenuState() { return menuState; }
	State* GetGameState() { return gameState; }
	State* GetEndState() { return endState; }

	int getWindowWidth() { return screenWidth; }
	int getWindowHeight() { return screenHeight; }

	float GetLifeTime() { return lifeTime; }

private:

	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The window renderer
	SDL_Renderer* renderer = nullptr;

	TTF_Font* font = nullptr;

	State* currentState = nullptr;
	State* menuState = nullptr;
	State* gameState = nullptr;
	State* endState = nullptr;

	Texture endTexture;

	int screenWidth = 1280;
	int screenHeight = 720;

	float deltaTime = 0.0f;
	float currentTime = 0.0f;
	float lastTime = 0.0f;
	float lifeTime = 0.0f;

	bool running = true;

};

