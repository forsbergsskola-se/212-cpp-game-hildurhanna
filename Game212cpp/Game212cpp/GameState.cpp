#include "GameState.h"

#include "Application.h"

GameState::GameState()
{
	foxTexture.loadFromFile("Images/foxcartoon.png");
	natureBackgroundTexture.loadFromFile("Images/nature_background.png");
	rulesTexture.loadFromFile("Images/rules.png");

	music = Mix_LoadMUS("Music/What_Does_The_Fox_Say_Loop3.ogg");

	foxPosX = (Application::GetInstance().getWindowWidth() / 2) + 30;
	foxPosY = (Application::GetInstance().getWindowHeight() / 2) + 20;
}

GameState::~GameState()
{
	//Free the music
	Mix_FreeMusic(music);
	music = nullptr;

	//Free loaded images
	natureBackgroundTexture.free();
	foxTexture.free();
}

void GameState::update(const float deltaTime)
{
	if (timerIncrement)
		timer += deltaTime;
}

void GameState::render()
{
	//Render background texture to screen
	natureBackgroundTexture.render(0, 0, Application::GetInstance().getWindowWidth(), Application::GetInstance().getWindowHeight());

	rulesTexture.render(50, 50, rulesTexture.getWidth(), rulesTexture.getHeight());

	//Render Fox to the screen
	foxTexture.render(foxPosX, foxPosY, foxTexture.getWidth(), foxTexture.getHeight());
}

void GameState::onMouseButtonDown()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	const SDL_FPoint mousePosition = { (float)mouseX, (float)mouseY };
	const SDL_FRect foxQuad = { (float)foxPosX, (float)foxPosY, (float)foxTexture.getWidth(), (float)foxTexture.getHeight() };

	if (SDL_PointInFRect(&mousePosition, &foxQuad))
	{
		if (!isMusicPlaying)
		{
			Mix_PlayMusic(music, -1);
			isMusicPlaying = true;

			timerIncrement = true;

			timer = 0.0f;
		}
	}
}

void GameState::onMouseButtonUp()
{
	if (isMusicPlaying)
	{
		Mix_HaltMusic();
		isMusicPlaying = false;

		timerIncrement = false;

		Application::GetInstance().GenerateEndTexture(timer);
		Application::GetInstance().SetState(Application::GetInstance().GetEndState());
	}
}