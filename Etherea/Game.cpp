#include "Game.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"
#include "TextureManager.hpp"
#include "Renderable.hpp"
#include "Snek.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const Uint32 FPS_CAP = 1001; //Unlimited (1000/1001==0)

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
	if (FPS_CAP <= 1000)
		SDL_Delay(1000 / FPS_CAP);
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
	objects["player"] = make_unique<Snek>();
	////////////////////////////
}

void Game::Cleanup()
{
	for (auto&& obj : objects)
		obj.second->clean();
}
