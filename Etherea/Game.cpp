#include "Game.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
#include "TextureManager.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : state(GameState::Uninitialized), evtHandler(*this) {}

void Game::Start()
{
	Init();
	state = GameState::Initialized;
	////////////////////////////
	TextureManager::getInstance(renderer).Load("snake", "../textures/char2-alpha.png");
	////////////////////////////
	while (state != +GameState::Exiting)
		GameLoop();
	Cleanup();
}

void Game::GameLoop()
{
	evtHandler.handleEvents();
	renderer.Clear();
	Update();
	renderer.Present();
}

void Game::Update()
{
	////////////////////////////
	TextureManager& tm = TextureManager::getInstance(renderer);
	int x = (int)((SCREEN_WIDTH - 134) * ((SDL_GetTicks() / 200) % 100) / 100.f);
	tm.Draw("snake", x, (SCREEN_HEIGHT - 134) / 2, 134, 134, (SDL_GetTicks() / 150) % 4, 0, SDL_FLIP_HORIZONTAL);
	////////////////////////////
}

void Game::Stop(StopReason reason)
{
	STDLOG << reason._to_string();
	state = GameState::Exiting;
}

void Game::Init()
{
	STDLOG << "Initializing";
	window = Window("Etherea", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = window.CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer.SetDrawColor(30, 30, 30);
}

void Game::Cleanup()
{
}
