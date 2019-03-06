#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "Music.hpp"
#include "SDLEventHandler.hpp"
#include "Renderable.hpp"
#include "Timer.hpp"

#define BETTER_ENUMS_NO_CONSTEXPR //Prevents some weird error
#include "Enum.hpp"

#include <map>

using std::map;

BETTER_ENUM(GameState, unsigned, Uninitialized, Initialized, Exiting)
BETTER_ENUM(StopReason, unsigned, Error, ExitEvent)

class Game {
	friend class SDLEventHandler;
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	Game();

	void Start();
	void Stop(StopReason);
private:
	void GameLoop();
	void Init();
	void Update();
	void Render();
	void Cleanup();
private:
	GameState state;
	Window window;
	Renderer renderer;
	SDLEventHandler evtHandler;
	map<string, unique_ptr<Renderable>> objects;
	map<SDL_TimerID, Timer> timers;
	Music music;
};
