#include "Exception.hpp"
#include "Common.hpp"

const char* SDLException::what() const
{
	return SDL_GetError();
}

const char* MixException::what() const
{
	return Mix_GetError();
}
