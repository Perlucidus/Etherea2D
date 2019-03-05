#include "Game.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
#include "TextureManager.hpp"
#include "Renderable.hpp"
#include "Entity.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : state(GameState::Uninitialized), evtHandler(*this) {}

void Game::Start()
{
	Init();
	state = GameState::Initialized;
	while (state != +GameState::Exiting)
		GameLoop();
	Cleanup();
}

void Game::GameLoop()
{
	evtHandler.handleEvents();
	Update();
	Render();
	SDL_Delay(100);
}

void Game::Update()
{
	for (auto&& obj : objects)
		obj.second->update();
}

void Game::Render()
{
	renderer.Clear();
	for (auto&& obj : objects)
		obj.second->draw(renderer);
	renderer.Present();
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
	////////////////////////////
	TextureManager::getInstance(renderer).Load("snake", "../textures/char2-alpha.png");
	objects["snake"] = make_unique<Entity>("snake", 0, Size(134, 134), Size(4, 1), SDL_FLIP_HORIZONTAL);
	////////////////////////////
}

void Game::Cleanup()
{
	for (auto&& obj : objects)
		obj.second->clean();
}
