#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Rect {
	friend class Renderer;
public:
	Rect() = default;
	Rect(Rect const& other) : data(other.data) {}
	Rect(int x, int y, int width, int height)
	{
		data.x = x;
		data.y = y;
		data.w = width;
		data.h = height;
	}
private:
	SDL_Rect data;
};
