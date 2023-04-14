#include "MenuState.h"

#include "Application.h"

MenuState::MenuState()
{
	SDL_Color textColor = { 0, 0, 0 };
	menuInfoTexture.loadFromRenderedText("Start the game by clicking on the screen, or exit the game by the 'X' icon", textColor);
}

MenuState::~MenuState()
{
	menuInfoTexture.free();
}


void MenuState::update(const float deltaTime)
{
}

void MenuState::render()
{
	menuInfoTexture.render((Application::GetInstance().getWindowWidth() - menuInfoTexture.getWidth()) / 2, (Application::GetInstance().getWindowHeight() - menuInfoTexture.getHeight()) / 2, menuInfoTexture.getWidth(), menuInfoTexture.getHeight());
}

void MenuState::onMouseButtonDown()
{
	Application::GetInstance().SetState(Application::GetInstance().GetGameState());
}

void MenuState::onMouseButtonUp()
{
}
