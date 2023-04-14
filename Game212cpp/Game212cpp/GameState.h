#pragma once

#include "State.h"

#include <SDL_mixer.h>

class GameState : public State
{
public:

	GameState();
	~GameState();

	virtual void update(const float deltaTime) override;
	virtual void render() override;
	virtual void onButtonMouseDown() override;
	virtual void onButtonMouseUp() override;

private:
	Texture foxTexture;
	Texture natureBackgroundTexture;
	Texture rulesTexture;

	//The music that will be played
	Mix_Music* music = nullptr;

	int foxPosX = 0;
	int foxPosY = 0;

	float timer = 0.0f;

	bool timerIncrement = false;
	bool isMusicPlaying = false;

};