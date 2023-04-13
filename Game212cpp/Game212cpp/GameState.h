#pragma once

#include "State.h"

class GameState : public State
{
public:

	GameState();
	~GameState();

	virtual void update() override;
	virtual void render() override;
	virtual void onButtonMouseDown() override;
	virtual void onButtonMouseUp() override;
};

