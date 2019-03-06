#include "Exception.hpp"
#include "Common.hpp"

const char* SDLException::what() const noexcept
{
	return SDL_GetError();
}

const char* MixException::what() const noexcept
{
	return Mix_GetError();
}
