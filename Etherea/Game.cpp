#include "Game.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"
#include "WindowEventHandler.hpp"
#include "Test.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double Game::TICK_RATE = 1. / 60.;

Game::Game() : state(GameState::Running), ticks(0) {}

Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

Window& Game::GetWindow()
{
	return window;
}

Renderer& Game::GetRenderer()
{
	return renderer;
}

void Game::EraseComponent(string const& id)
{
	if (!components.erase(id))
		throw std::logic_error("Key not found");
}

void Game::Start()
{
	try {
		Init();
		lastTick = SDL_GetTicks();
		while (state != +GameState::Exiting)
			GameLoop();
	}
	catch (std::exception const& e) { ERRLOG << e.what(); }
	Cleanup();
}

double Game::GetTicks() const
{
	return ticks;
}

void Game::GameLoop()
{
	HandleEvents();
	double tick = SDL_GetTicks();
	double loopTime = tick - lastTick;
	lastTick = tick;
	while (loopTime >= TICK_RATE) {
		Update();
		loopTime -= TICK_RATE;
		ticks += TICK_RATE;
	}
	lastTick -= loopTime;
	Render();
}

void Game::Update()
{
	for (auto&& component : components)
		component.second->Update();
}

void Game::Render()
{
	renderer.Clear();
	for (auto&& component : components)
		component.second->Render(renderer);
	renderer.Present();
}

void Game::Stop(StopReason reason, bool cleanup)
{
	STDLOG << reason._to_string();
	state = GameState::Exiting;
	if (cleanup) Cleanup();
}

void Game::Init()
{
	STDLOG << "Initializing";
	window = Window("Etherea", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = window.CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	renderer.SetDrawColor(Color(30, 30, 30));
	RegisterEventHandler<WindowEventHandler>(EventHandlerPriority::WINDOW);
	////////////////////////////////////////////////////////////////////////////////////
	AddComponent<TestComponent>("test");
	////////////////////////////////////////////////////////////////////////////////////
	AddComponent<SplashScreen>("splash").Init();
}

void Game::HandleEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
		for (auto&& handler : eventHandlers)
			handler.second->Handle(evt);
		if (evt.type == SDL_QUIT)
			Stop(StopReason::QuitEvent, false);
	}
}

void Game::Cleanup()
{
	for (auto&& timer : timers)
		timer.second.abort();
	for (auto&& component : components)
		component.second->Cleanup();
}
