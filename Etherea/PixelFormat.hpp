#pragma once

#include "Common.hpp"
#include "Exception.hpp"

class Window;

using Pixel = Uint32;

class PixelFormat {
public:
	PixelFormat() = default;
	PixelFormat(PixelFormat const&) = default;

	explicit PixelFormat(SDL_PixelFormat* format);

	string GetName() const;
	Pixel MapRGB(SDL_Color const& color) const;
	Pixel MapRGBA(SDL_Color const& color) const;
	SDL_Color GetRGB(Pixel pixel) const;
	SDL_Color GetRGBA(Pixel pixel) const;
private:
	shared_ptr<SDL_PixelFormat> ptr;
};

class PixelFormatException : public SDLException {};
