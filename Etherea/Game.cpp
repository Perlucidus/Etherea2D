#include "Game.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"
#include "WindowEventHandler.hpp"
#include "Test.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const Uint32 FPS_CAP = 1001; //Unlimited (1000/1001==0)

Game::Game() : state(GameState::Running) {}

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
		while (state != +GameState::Exiting)
			GameLoop();
	}
	catch (std::exception const& e) { ERRLOG << e.what(); }
	Cleanup();
}

void Game::GameLoop()
{
	HandleEvents();
	Update();
	Render();
	if (FPS_CAP <= 1000)
		SDL_Delay(1000 / FPS_CAP);
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
	components["splash"] = make_unique<SplashScreen>();
	////////////////////////////////////////////////////////////////////////////////////
	components["test"] = make_unique<TestComponent>();
	////////////////////////////////////////////////////////////////////////////////////
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
