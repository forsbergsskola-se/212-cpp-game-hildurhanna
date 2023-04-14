#pragma once

#include "Texture.h"

class State
{
public:

	State() {}
	virtual ~State() {}
	virtual void update(const float deltaTime) = 0;
	virtual void render() = 0;
	virtual void onButtonMouseDown() = 0;
	virtual void onButtonMouseUp() = 0;
};

