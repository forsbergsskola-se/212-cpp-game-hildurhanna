#pragma once

class State
{
public:

	State() {}
	virtual ~State() {}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onButtonMouseDown() = 0;
	virtual void onButtonMouseUp() = 0;
};

