#include "PixelFormat.hpp"
#include "Window.hpp"

PixelFormat::PixelFormat(SDL_PixelFormat* format)
{
	ptr = shared_ptr<SDL_PixelFormat>(format, [=](SDL_PixelFormat* p) { if (p) SDL_FreeFormat(p); STDLOG << "Pixel Format Destroyed"; });
	if (!ptr) throw PixelFormatException();
}

string PixelFormat::GetName() const
{
	if (!ptr) throw PixelFormatException();
	return SDL_GetPixelFormatName(ptr->format);
}

Pixel PixelFormat::MapRGB(SDL_Color const& color) const
{
	if (!ptr) throw PixelFormatException();
	return SDL_MapRGB(ptr.get(), color.r, color.g, color.b);
}

Pixel PixelFormat::MapRGBA(SDL_Color const& color) const
{
	if (!ptr) throw PixelFormatException();
	return SDL_MapRGBA(ptr.get(), color.r, color.g, color.b, color.a);
}

SDL_Color PixelFormat::GetRGB(Pixel pixel) const
{
	SDL_Color color;
	SDL_GetRGB(pixel, ptr.get(), &color.r, &color.g, &color.b);
	return color;
}

SDL_Color PixelFormat::GetRGBA(Pixel pixel) const
{
	SDL_Color color;
	SDL_GetRGBA(pixel, ptr.get(), &color.r, &color.g, &color.b, &color.a);
	return color;
}
