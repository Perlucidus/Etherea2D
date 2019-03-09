#pragma once

#include "Log.hpp"
#include "Exception.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_timer.h>
#include <memory>

using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;

inline SDL_Color Color(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha = SDL_ALPHA_OPAQUE) {
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = alpha;
	return color;
}
