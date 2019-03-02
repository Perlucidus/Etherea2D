#include "Common.hpp"
#include "SDLComponent.hpp"

void SDLComponent::setError(bool s)
{
	if (!(success = s)) {
		error = SDL_GetError();
		ERRLOG << error;
	}
}

string const& SDLComponent::getError() const
{
	return error;
}
