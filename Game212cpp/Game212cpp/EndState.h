#pragma once

#include "State.h"

class EndState : public State
{
public:

	EndState();
	~EndState();

	virtual void update(const float deltaTime) override;
	virtual void render() override;
	virtual void onMouseButtonDown() override;
	virtual void onMouseButtonUp() override;

private:
	Texture endFoxLeftTopTexture;
	Texture endFoxRightBottomTexture;

	float sinus = 0.0f;
	float cosinus = 0.0f;

};

