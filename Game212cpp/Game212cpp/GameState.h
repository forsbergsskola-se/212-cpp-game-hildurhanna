#pragma once

#include "State.h"

class GameState : public State
{
	virtual void handleEvents() override;
	virtual void updates() override;
	virtual void render() override;
};

