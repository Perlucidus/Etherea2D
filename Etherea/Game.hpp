#pragma once

#include "Common.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "SDLEventHandler.hpp"

#define BETTER_ENUMS_NO_CONSTEXPR
#include "Enum.hpp"

BETTER_ENUM(GameState, unsigned, Uninitialized, Initialized, Exiting)
BETTER_ENUM(StopReason, unsigned, Error, ExitEvent)

class Game {
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	Game();

	void Start();
	void Stop(StopReason);
private:
	void GameLoop();
	void init();
	void cleanup();
private:
	GameState state;
	Window* window;
	Renderer* renderer;
	SDLEventHandler evtHandler;
};
