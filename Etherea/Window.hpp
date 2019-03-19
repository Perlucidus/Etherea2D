#pragma once

#include "Common.hpp"
#include "Exception.hpp"
#include <SDL_video.h>

class Renderer;
class PixelFormat;

class Window {
public:
	Window() = default;
	Window(string name, int x, int y, int width, int height, Uint32 flags);
	Window(string name, int width, int height, Uint32 flags);
	virtual ~Window() = default;

	Renderer CreateRenderer(Uint32 flags);
	Renderer CreateRenderer(int index, Uint32 flags);
	PixelFormat GetPixelFormat();
	string GetTitle();
	void SetTitle(string const& title);
private:
	shared_ptr<SDL_Window> ptr;
};

class WindowException : public SDLException {};
