#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Window : public SDLComponent {
public:
	Window() = delete;

	Window(string name, int x, int y, int width, int height, Uint32 flags);
	Window(string name, int width, int height, Uint32 flags);
	virtual ~Window();

	SDL_Window* getSDLWindow();
private:
	SDL_Window* ptr;
};
