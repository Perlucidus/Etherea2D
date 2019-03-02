#include "Common.hpp"
#include "SDLComponent.hpp"

SDLComponent::SDLComponent(SDLComponent const& other) : success(other.success), error(other.error) {}

void SDLComponent::setError(bool s)
{
	if (!(success = s))
		error = SDL_GetError();
}

string const& SDLComponent::getError() const
{
	return error;
}
