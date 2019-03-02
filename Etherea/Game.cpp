#include "Game.hpp"
#include "Texture.hpp"
#include "Rect.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : state(GameState::Uninitialized), evtHandler(*this) {}

////////////////////////////
Texture t;
Rect src, dst;
////////////////////////////

void Game::Start()
{
	Init();
	state = GameState::Initialized;
	////////////////////////////
	t = renderer.LoadTextureBMP("../textures/char2.bmp");
	src = Rect(134, 134);
	//t.Query(src->x, src->y);
	dst = src;
	dst->x = SCREEN_WIDTH - dst->w;
	dst->y = (SCREEN_HEIGHT - dst->h)/2;
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
	src->x = 134 * (int)((SDL_GetTicks() / 150) % 4);
	dst->x = (int)((SCREEN_WIDTH - dst->w) * (1 - ((SDL_GetTicks() / 200) % 100) / 100.f));
	renderer.Copy(t, src, dst);
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
}

void Game::Cleanup()
{
}
