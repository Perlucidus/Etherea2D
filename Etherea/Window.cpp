#include "Window.hpp"

Window::Window(string name, int x, int y, int width, int height, Uint32 flags)
{
	window = SDL_CreateWindow(name.c_str(), x, y, width, height, flags);
	setError(window);
}

Window::Window(string name, int width, int height, Uint32 flags)
	: Window(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags) {}

Window::~Window()
{
	if (window)
		SDL_DestroyWindow(window);
}

SDL_Window* Window::getSDLWindow()
{
	return window;
}
