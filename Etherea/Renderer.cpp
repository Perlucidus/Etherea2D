#include "Renderer.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Rect.hpp"

Renderer::Renderer(SDL_Renderer* renderer)
{
	ptr = shared_ptr<SDL_Renderer>(renderer, [=](SDL_Renderer* p) { if (p) SDL_DestroyRenderer(p); STDLOG << "Renderer Destroyed"; });
	setError(ptr.get());
}

void Renderer::Clear()
{
	if (SDL_RenderClear(ptr.get()))
		throw; //TODO RenderException
}

void Renderer::Present()
{
	SDL_RenderPresent(ptr.get());
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
	if (SDL_SetRenderDrawColor(ptr.get(), r, g, b, alpha))
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
	return Texture(SDL_CreateTextureFromSurface(ptr.get(), surface.ptr.get()));
}

Texture Renderer::LoadTextureBMP(string const & path)
{
	return CreateFromSurface(Surface::FromBMP(path));
}

void Renderer::copy(Texture const & texture, const Rect * from, const Rect * to)
{
	const SDL_Rect *src = nullptr, *dst = nullptr;
	if (from) src = &from->data;
	if (to) dst = &to->data;
	if (SDL_RenderCopy(ptr.get(), texture.ptr.get(), src, dst))
		throw; //TODO RenderException
}
