#include "Surface.hpp"
#include "Log.hpp"
#include <SDL_image.h>

Surface::Surface(SDL_Surface* surface)
{
	ptr = shared_ptr<SDL_Surface>(surface, [=](SDL_Surface* p) { if (p) SDL_FreeSurface(p); STDLOG << "Surface Destroyed"; });
	if (!ptr) throw SurfaceException();
}

Surface Surface::LoadIMG(string const& path)
{
	return Surface(IMG_Load(path.c_str()));
}

SDL_Color Surface::GetColorMod()
{
	SDL_Color color;
	if (SDL_GetSurfaceColorMod(ptr.get(), &color.r, &color.g, &color.b) || SDL_GetSurfaceAlphaMod(ptr.get(), &color.a))
		throw SurfaceException();
	return color;
}

void Surface::ColorMod(SDL_Color const& color)
{
	if (SDL_SetSurfaceColorMod(ptr.get(), color.r, color.g, color.b) || SDL_SetSurfaceAlphaMod(ptr.get(), color.a))
		throw SurfaceException();
}

void Surface::ClearColorMod()
{
	SDL_Color color;
	color.r = color.g = color.b = 255;
	color.a = SDL_ALPHA_OPAQUE;
	ColorMod(color);
}
