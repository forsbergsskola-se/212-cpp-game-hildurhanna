#pragma once

class State
{
	State() {}
	virtual ~State() {}
	virtual void handleEvents() = 0;
	virtual void updates() = 0;
	virtual void render() = 0;
};

