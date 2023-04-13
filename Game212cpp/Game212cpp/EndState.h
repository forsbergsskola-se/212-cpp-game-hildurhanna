#pragma once

#include "State.h"

class EndState : public State
{
	EndState();
	~EndState();

	virtual void handleEvents() override;
	virtual void updates() override;
	virtual void render() override;
};

