#pragma once

#include "State.h"

class MenuState : public State
{
public:

	MenuState();
	~MenuState();

	virtual void update(const float deltaTime) override;
	virtual void render() override;
	virtual void onMouseButtonDown() override;
	virtual void onMouseButtonUp() override;

private:
	Texture menuInfoTexture;
	
};

