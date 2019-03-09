#include "WindowEventHandler.hpp"
#include "Game.hpp"
/////////////////////////////
#include "Test.hpp"
/////////////////////////////

const int WindowEventHandler::PRIORITY = 1000;

void WindowEventHandler::Handle(SDL_Event const& event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		break;
	case SDL_USEREVENT:
		STDLOG << "User Event " << CustomEvent::_from_integral(event.user.code)._to_string();
		///////////////////////////////////////////////
		if (event.user.code == CustomEvent::SPLASH) {
			GAME.GetComponent("test").EraseObject("splash");
			GAME.GetComponent("test").GetObject<Snek>("player").show();
		}
		///////////////////////////////////////////////
		break;
	}
}
