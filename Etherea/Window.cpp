#include "Window.hpp"
#include "Renderer.hpp"

Window::Window(string name, int x, int y, int width, int height, Uint32 flags)
{
	ptr = shared_ptr<SDL_Window>(
		SDL_CreateWindow(name.c_str(), x, y, width, height, flags),
		[=](SDL_Window* p) { if (p) SDL_DestroyWindow(p); STDLOG << "Window Destroyed"; });
	setError(ptr.get());
}

Window::Window(string name, int width, int height, Uint32 flags)
	: Window(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags) {}

Renderer Window::CreateRenderer(Uint32 flags)
{
	return CreateRenderer(-1, flags);
}

Renderer Window::CreateRenderer(int index, Uint32 flags)
{
	return Renderer(SDL_CreateRenderer(ptr.get(), index, flags));
}
