#pragma once

#include "EventHandler.hpp"

class WindowEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual bool handle(SDL_Event const& event) override;
};
