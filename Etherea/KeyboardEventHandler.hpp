#pragma once

#include "EventHandler.hpp"
#include "Vector2D.hpp"

class KeyboardEventHandler : public EventHandler {
public:
	static const int PRIORITY;

	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
private:
	void KeyDown(SDL_KeyboardEvent const& event);
	void KeyUp(SDL_KeyboardEvent const& event);

	Direction GetKeyDirection(SDL_Keycode key);
};
