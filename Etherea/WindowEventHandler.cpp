#include "WindowEventHandler.hpp"
#include "Game.hpp"

bool WindowEventHandler::handle(SDL_Event const& event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		return true;
	}
	return false;
}
