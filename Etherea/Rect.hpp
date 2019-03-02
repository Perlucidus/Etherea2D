#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Rect {
	friend class Renderer;
public:
	Rect() { data.x = data.y = data.w = data.h = 0; }
	Rect(Rect const& other) : data(other.data) {}
	Rect(int width, int height) : Rect(0, 0, width, height) {}
	Rect(int x, int y, int width, int height)
	{
		data.x = x;
		data.y = y;
		data.w = width;
		data.h = height;
	}

	SDL_Rect* operator->() { return &data; }
	const SDL_Rect* operator->() const { return &data; }
private:
	SDL_Rect data;
};
