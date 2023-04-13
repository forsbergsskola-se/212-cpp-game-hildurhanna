#pragma once

#include "State.h"

class EndState : public State
{
public:

	EndState();
	~EndState();

	virtual void update() override;
	virtual void render() override;
	virtual void onButtonMouseDown() override;
	virtual void onButtonMouseUp() override;
};

