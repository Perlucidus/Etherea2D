#include "SDLEventHandler.hpp"
#include "Game.hpp"
#include "Snek.hpp"

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
	case SDL_KEYUP:
		keyboard(evt.key);
		break;
	}
}

void SDLEventHandler::keyboard(SDL_KeyboardEvent const& evt)
{
	Snek& player = static_cast<Snek&>(*game.objects["player"]);
	Direction d;
	switch (evt.keysym.sym) {
	case SDLK_LEFT:
	case SDLK_RIGHT:
		d = Direction(static_cast<float>(evt.keysym.sym == SDLK_LEFT ? -1 : 1), 0);
		if (evt.type == SDL_KEYDOWN) {
			player.setFacingDirection(d);
			player.setMoving(true);
		}
		else if (evt.type == SDL_KEYUP && player.getFacingDirection() == d)
			player.setMoving(false);
		break;
	}
}
