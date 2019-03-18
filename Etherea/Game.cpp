#include "Game.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"
#include "WindowEventHandler.hpp"
#include "Test.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double Game::TICK_RATE = 1000. / 180.; //180 ticks per second

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
		last_tick = SDL_GetTicks();
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
	double frameTime = tick - last_tick;
	fps = 1000 / frameTime; //LOG
	last_tick = tick;
	while (frameTime >= TICK_RATE) {
		Update();
		frameTime -= TICK_RATE;
		ticks += TICK_RATE;
	}
	last_tick -= frameTime;
	Render();
}

void Game::Update()
{
	if (SDL_GetTicks() - last_status_update > 100) {
		window.SetTitle("Etherea | " + std::to_string(static_cast<int>(fps)) + " FPS");
		last_status_update = SDL_GetTicks();
	}
	for (auto&& component : components)
		component.second->update();
}

void Game::Render()
{
	renderer.SetDrawColor(Color(30, 30, 30)); //Default bg
	renderer.Clear();
	for (auto&& component : components)
		component.second->render(renderer);
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
	renderer = window.CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer.SetScreenSize(Size(SCREEN_WIDTH, SCREEN_HEIGHT));
	RegisterEventHandler<WindowEventHandler>(EventHandlerPriority::WINDOW);
	////////////////////////////////////////////////////////////////////////////////////
	AddComponent<TestWorld>("test");
	////////////////////////////////////////////////////////////////////////////////////
	AddComponent<SplashScreen>("splash").initialize();
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
	timers.clear();
	for (auto&& component : components)
		component.second->clean();
	components.clear();
}
