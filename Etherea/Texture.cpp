#include "Texture.hpp"

Texture::Texture(SDL_Texture* texture)
{
	ptr = shared_ptr<SDL_Texture>(texture, [=](SDL_Texture* p) { if (p) SDL_DestroyTexture(p); STDLOG << "Texture Destroyed"; });
	if (!ptr) throw TextureException();
}

void Texture::Query(int & width, int & height)
{
	query(nullptr, nullptr, &width, &height);
}

void Texture::Query(Uint32& format, int& access, int& width, int& height)
{
	query(&format, &access, &width, &height);
}

void Texture::query(Uint32* format, int* access, int* width, int* height)
{
	if (SDL_QueryTexture(ptr.get(), format, access, width, height))
		throw TextureException();
}
