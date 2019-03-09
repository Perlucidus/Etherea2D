#pragma once

#include "EventHandler.hpp"

class WindowEventHandler : public EventHandler {
public:
	static const int PRIORITY;

	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
};
