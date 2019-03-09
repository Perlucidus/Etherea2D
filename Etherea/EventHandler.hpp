#pragma once

#include "Common.hpp"

BETTER_ENUM(CustomEvent, Sint32, SPLASH)

class EventHandler {
public:
	EventHandler() = default;
	virtual ~EventHandler() = default;
	EventHandler(EventHandler const&) = delete;
	void operator=(EventHandler const&) = delete;

	virtual void Handle(SDL_Event const&) = 0;
};
