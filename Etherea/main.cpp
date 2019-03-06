#include "Game.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		ERRLOG << SDL_GetError();
		return 1;
	}
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, MIX_DEFAULT_CHANNELS, 4096);
	Mix_VolumeMusic(static_cast<int>(MIX_MAX_VOLUME * 0.01));
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
