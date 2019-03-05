#include "Game.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		ERRLOG << SDL_GetError();
		return 1;
	}
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	try {
		Game().Start();
	}
	catch (...) {
		ERRLOG << SDL_GetError();
	}
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}
