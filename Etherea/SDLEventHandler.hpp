#pragma once

#include "Common.hpp"

class Game;

class SDLEventHandler {
public:
	SDLEventHandler(Game&);

	void handleEvents();
private:
	void handle(SDL_Event const&);
	void keyboard(SDL_KeyboardEvent const&);
private:
	Game& game;
};
