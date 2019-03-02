#include "SDLEventHandler.hpp"
#include "Game.hpp"

SDLEventHandler::SDLEventHandler(Game& game) : game(game) {}

void SDLEventHandler::handleEvents()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
		handle(evt);
}

void SDLEventHandler::handle(SDL_Event const& evt)
{
	switch (evt.type) {
	case SDL_QUIT:
		STDLOG << "SDL_QUIT Event";
		game.Stop(StopReason::ExitEvent);
		break;
	case SDL_KEYDOWN:
		keyboard(evt.key);
		break;
	}
}

void SDLEventHandler::keyboard(SDL_KeyboardEvent const& evt)
{

}
