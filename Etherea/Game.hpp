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
public:
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game();
public:
	static Game& GetInstance();

	Window& GetWindow();
	Renderer& GetRenderer();

	template<typename ComponentT>
	ComponentT& AddComponent(string const& id);
	template<typename ComponentT>
	ComponentT& GetComponent(string const& id);
	void EraseComponent(string const& id);

	void Start();
	void Stop(StopReason reason, bool cleanup);
	template<typename EventHandlerT>
	void RegisterEventHandler(int priority);
	double GetTicks() const;
private:
	void GameLoop();
	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Cleanup();
public:
	static const double TICK_RATE;
private:
	double ticks, last_tick, loopTime;
	GameState state;
	Window window;
	Renderer renderer;
	map<int, unique_ptr<EventHandler>> eventHandlers;
	map<string, unique_ptr<GameComponent>> components;
	map<SDL_TimerID, Timer> timers;
	//LOG
	double fps, last_status_update;
};

template<typename ComponentT>
inline ComponentT& Game::AddComponent(string const& id)
{
	return AddUniqueValueRef<ComponentT>(components, id);
}

template<typename ComponentT>
inline ComponentT& Game::GetComponent(string const& id)
{
	return GetUniqueValueRef<ComponentT>(components, id);
}

template<typename EventHandlerT>
inline void Game::RegisterEventHandler(int priority)
{
	eventHandlers[priority] = make_unique<EventHandlerT>();
}
