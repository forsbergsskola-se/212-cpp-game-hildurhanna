#pragma once

#include "State.h"

class EndState : public State
{
public:

	EndState();
	~EndState();

	virtual void update(const float deltaTime) override;
	virtual void render() override;
	virtual void onButtonMouseDown() override;
	virtual void onButtonMouseUp() override;

private:
	Texture endFoxLeftTopTexture;
	Texture endFoxRightBottomTexture;

	float sinus = 0.0f;
	float cosinus = 0.0f;

};

