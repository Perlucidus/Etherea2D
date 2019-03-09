#include "KeyboardEventHandler.hpp"
#include "Game.hpp"
#include "Random.hpp"
#include "Test.hpp"

const int KeyboardEventHandler::PRIORITY = 2000;

void KeyboardEventHandler::Handle(SDL_Event const& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
		KeyDown(event.key);
		break;
	case SDL_KEYUP:
		KeyUp(event.key);
		break;
	}
}

void KeyboardEventHandler::KeyDown(SDL_KeyboardEvent const& event)
{
	Snek& player = GAME.GetComponent("test").GetObject<Snek>("player");
	Direction d;
	Random rnd;
	switch (event.keysym.sym) {
	case SDLK_LEFT:
	case SDLK_RIGHT:
		player.setFacingDirection(GetKeyDirection(event.keysym.sym));
		player.setMoving(true);
		break;
	case SDLK_UP:
		player.changeColor(Color(rnd.next(256), rnd.next(256), rnd.next(256)));
		break;
	case SDLK_DOWN:
		player.changeColor(Color(255, 255, 255));
		break;
	}
}

void KeyboardEventHandler::KeyUp(SDL_KeyboardEvent const& event)
{
	Snek& player = GAME.GetComponent("test").GetObject<Snek>("player");
	Direction d;
	Random rnd;
	switch (event.keysym.sym) {
	case SDLK_LEFT:
	case SDLK_RIGHT:
		d = Direction(static_cast<float>(event.keysym.sym == SDLK_LEFT ? -1 : 1), 0);
		if (player.getFacingDirection() == d)
			player.setMoving(false);
		break;
	}
}

Direction KeyboardEventHandler::GetKeyDirection(SDL_Keycode key)
{
	float x, y;
	x = y = 0;
	switch (key) {
	case SDLK_RIGHT:
		x = 1;
		break;
	case SDLK_LEFT:
		x = -1;
		break;
	case SDLK_DOWN:
		y = -1;
		break;
	case SDLK_UP:
		y = 1;
		break;
	}
	return Direction(x, y);
}
