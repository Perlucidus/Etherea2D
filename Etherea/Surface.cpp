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
