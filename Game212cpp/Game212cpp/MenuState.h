#pragma once

#include "State.h"

class MenuState : public State
{
public:

	MenuState();
	~MenuState();

	virtual void update(const float deltaTime) override;
	virtual void render() override;
	virtual void onButtonMouseDown() override;
	virtual void onButtonMouseUp() override;

private:
	Texture menuInfoTexture;
	
};

