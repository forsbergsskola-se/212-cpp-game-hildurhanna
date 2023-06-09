#include "EndState.h"

#include "Application.h"

EndState::EndState()
{
	endFoxLeftTopTexture.loadFromFile("Images/fox2.png");
	endFoxRightBottomTexture.loadFromFile("Images/fox.png");
}

EndState::~EndState()
{
}


void EndState::update(const float deltaTime)
{
	const float lifeTime = Application::GetInstance().GetLifeTime();

	sinus = sinf(lifeTime * 4.0f);
	cosinus = cosf(lifeTime * 4.0f);
}

void EndState::render()
{
	Texture& texture = Application::GetInstance().GetEndTexture();
	const int windowWidth = Application::GetInstance().getWindowWidth();
	const int windowHeight = Application::GetInstance().getWindowHeight();

	texture.render((windowWidth - texture.getWidth()) / 2, (windowHeight - texture.getHeight()) / 2, texture.getWidth(), texture.getHeight());

	int xFoxLeftTopTexture{ static_cast<int>(-endFoxLeftTopTexture.getWidth() + (cosinus * 300.0f)) };
	int yFoxLeftTopTexture{ static_cast<int>(-endFoxLeftTopTexture.getHeight() + (cosinus * 300.0f)) };
	int xFoxRightBottomTexture{ static_cast<int>(windowWidth - (sinus * 300.0f)) };
	int yFoxRightBottomTexture{ static_cast<int>(windowHeight - (sinus * 300.0f)) };
	endFoxLeftTopTexture.render(xFoxLeftTopTexture, yFoxLeftTopTexture, endFoxLeftTopTexture.getWidth(), endFoxLeftTopTexture.getHeight());
	endFoxRightBottomTexture.render(xFoxRightBottomTexture, yFoxRightBottomTexture, endFoxRightBottomTexture.getWidth(), endFoxRightBottomTexture.getHeight());
}

void EndState::onMouseButtonDown()
{
	Application::GetInstance().SetState(Application::GetInstance().GetMenuState());
}

void EndState::onMouseButtonUp()
{

}
