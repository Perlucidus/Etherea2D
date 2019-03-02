#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture) : ptr(texture) {}

Texture::~Texture()
{
	if (ptr)
		SDL_DestroyTexture(ptr);
}

Texture::Texture(Texture const& other) : ptr(other.ptr) {}

void Texture::Query(Uint32& format, int& access, int& width, int& height)
{
	if (SDL_QueryTexture(ptr, &format, &access, &width, &height))
		throw; //TODO TextureException
}
