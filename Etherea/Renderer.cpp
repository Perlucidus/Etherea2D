#include "Renderer.hpp"

Renderer::Renderer(Window* window, int index, Uint32 flags) : window(window)
{
	ptr = SDL_CreateRenderer(window->getSDLWindow(), index, flags);
	setError(ptr);
}

Renderer::Renderer(Window* window, Uint32 flags) : Renderer(window, -1, flags) {}

Renderer::~Renderer()
{
	if (ptr)
		SDL_DestroyRenderer(ptr);
}

void Renderer::Clear()
{
	if (SDL_RenderClear(ptr))
		throw; //TODO RenderException
}

void Renderer::Present()
{
	SDL_RenderPresent(ptr);
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
	if (SDL_SetRenderDrawColor(ptr, r, g, b, alpha))
		throw; //TODO RenderException
}

void Renderer::Copy(Texture const& texture, Rect const & from, Rect const & to)
{
	copy(texture, &from, &to);
}

void Renderer::CopyFrom(Texture const & texture, Rect const & from)
{
	copy(texture, &from);
}

void Renderer::CopyTo(Texture const & texture, Rect const & to)
{
	copy(texture, nullptr, &to);
}

Texture Renderer::CreateFromSurface(Surface const & surface)
{
	return Texture(SDL_CreateTextureFromSurface(ptr, surface.ptr));
}

void Renderer::copy(Texture const & texture, const Rect * from, const Rect * to)
{
	const SDL_Rect *src = nullptr, *dst = nullptr;
	if (from) src = &from->data;
	if (to) dst = &to->data;
	if (SDL_RenderCopy(ptr, texture.ptr, src, dst))
		throw; //TODO: RenderException
}
