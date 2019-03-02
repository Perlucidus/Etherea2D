#include "Game.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : state(GameState::Uninitialized), evtHandler(*this) {}

void Game::Start()
{
	init();
	state = GameState::Initialized;
	while (state != +GameState::Exiting)
		GameLoop();
	cleanup();
}

void Game::GameLoop()
{
	evtHandler.handleEvents();
	renderer->Clear();
	renderer->Present();
}

void Game::Stop(StopReason reason)
{
	STDLOG << reason._to_string();
	state = GameState::Exiting;
}

void Game::init()
{
	STDLOG << "Initializing";
	window = new Window("Etherea", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = new Renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Game::cleanup()
{
	delete renderer;
	delete window;
}
