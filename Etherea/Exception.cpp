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

TimerException::TimerException() : reason(nullptr) {}

TimerException::TimerException(char const* reason) : reason(reason) {}

char const* TimerException::what() const noexcept
{
	if (reason)
		return reason;
	return SDLException::what();
}
