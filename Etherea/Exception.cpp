#include "Exception.hpp"
#include <SDL_mixer.h>

const char* SDLException::what() const noexcept
{
	return SDL_GetError();
}

const char* MixException::what() const noexcept
{
	return Mix_GetError();
}
