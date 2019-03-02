#include "Game.hpp"

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	try {
		Game().Start();
	}
	catch (...) {
		ERRLOG << SDL_GetError();
	}
	SDL_Quit();
	return 0;
}
