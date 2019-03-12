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
	double ticks, lastTick;
	GameState state;
	Window window;
	Renderer renderer;
	map<int, unique_ptr<EventHandler>> eventHandlers;
	map<string, unique_ptr<GameComponent>> components;
	map<SDL_TimerID, Timer> timers;
};

template<typename ComponentT>
inline ComponentT& Game::AddComponent(string const& id)
{
	static_assert(std::is_base_of<GameComponent, ComponentT>::value, "Invalid type argument");
	auto lb = components.lower_bound(id);
	if (lb != components.end() && !(components.key_comp()(id, lb->first)))
		throw std::logic_error("Key already exists");
	auto component = components.insert(lb, map<string, unique_ptr<ComponentT>>::value_type(id, make_unique<ComponentT>()));
	return static_cast<ComponentT&>(*component->second);
}

template<typename ComponentT>
inline ComponentT& Game::GetComponent(string const& id)
{
	static_assert(std::is_base_of<GameComponent, ComponentT>::value, "Invalid type argument");
	auto it = components.find(id);
	if (it == components.end())
		throw std::logic_error("Key not found");
	return dynamic_cast<ComponentT&>(*it->second);
}

template<typename EventHandlerT>
inline void Game::RegisterEventHandler(int priority)
{
	eventHandlers[priority] = make_unique<EventHandlerT>();
}
