#pragma once

#include "EventHandler.hpp"

class WindowEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
};
