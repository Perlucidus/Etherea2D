#include "Surface.hpp"

Surface::Surface(SDL_Surface* surface)
{
	ptr = shared_ptr<SDL_Surface>(surface, [=](SDL_Surface* p) { if (p) SDL_FreeSurface(p); STDLOG << "Surface Destroyed"; });
	if (!ptr) throw SurfaceException();
}

Surface Surface::LoadIMG(string const& path)
{
	return Surface(IMG_Load(path.c_str()));
}

void Surface::GetColorMod(Uint8 & r, Uint8 & g, Uint8 & b)
{
	if (SDL_GetSurfaceColorMod(ptr.get(), &r, &g, &b))
		throw SurfaceException();
}

void Surface::ColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	if (SDL_SetSurfaceColorMod(ptr.get(), r, g, b))
		throw SurfaceException();
}

void Surface::ClearColorMod()
{
	ColorMod(255, 255, 255);
}

void Surface::GetAlphaMod(Uint8 & alpha)
{
	if (SDL_GetSurfaceAlphaMod(ptr.get(), &alpha))
		throw SurfaceException();
}

void Surface::AlphaMod(Uint8 alpha)
{
	if (SDL_SetSurfaceAlphaMod(ptr.get(), alpha))
		throw SurfaceException();
}

void Surface::ClearAlphaMod()
{
	AlphaMod(SDL_ALPHA_OPAQUE);
}
