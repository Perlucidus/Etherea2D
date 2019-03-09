#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "Music.hpp"
#include "EventHandler.hpp"
#include "GameComponent.hpp"
#include "Timer.hpp"

#define BETTER_ENUMS_NO_CONSTEXPR //Prevents some weird error
#include "Enum.hpp"

#include <map>

using std::map;

#define GAME Game::GetInstance()

BETTER_ENUM(GameState, unsigned, Running, Exiting)
BETTER_ENUM(StopReason, unsigned, Error, QuitEvent)

class Game {
	friend class WindowEventHandler;
	friend class KeyboardEventHandler;
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game();
public:
	static Game& GetInstance();

	Window& GetWindow();
	Renderer& GetRenderer();
	GameComponent& GetComponent(string const& id);

	void Start();
	void Stop(StopReason reason, bool cleanup);
private:
	void GameLoop();
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Cleanup();
private:
	GameState state;
	Window window;
	Renderer renderer;
	map<int, unique_ptr<EventHandler>> eventHandlers;
	map<string, unique_ptr<GameComponent>> components;
	map<SDL_TimerID, Timer> timers;
	Music music;
};
