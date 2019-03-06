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

void Texture::Query(Size & size)
{
	int w, h;
	Query(w, h);
	size = Size(w, h);
}

void Texture::Query(Uint32& format, int& access, int& width, int& height)
{
	query(&format, &access, &width, &height);
}

void Texture::GetColorMod(Uint8 & r, Uint8 & g, Uint8 & b)
{
	if (SDL_GetTextureColorMod(ptr.get(), &r, &g, &b))
		throw SurfaceException();
}

void Texture::ColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	if (SDL_SetTextureColorMod(ptr.get(), r, g, b))
		throw SurfaceException();
}

void Texture::ClearColorMod()
{
	ColorMod(255, 255, 255);
}

void Texture::GetAlphaMod(Uint8 & alpha)
{
	if (SDL_GetTextureAlphaMod(ptr.get(), &alpha))
		throw SurfaceException();
}

void Texture::AlphaMod(Uint8 alpha)
{
	if (SDL_SetTextureAlphaMod(ptr.get(), alpha))
		throw SurfaceException();
}

void Texture::ClearAlphaMod()
{
	AlphaMod(SDL_ALPHA_OPAQUE);
}

void Texture::query(Uint32* format, int* access, int* width, int* height)
{
	if (SDL_QueryTexture(ptr.get(), format, access, width, height))
		throw TextureException();
}
