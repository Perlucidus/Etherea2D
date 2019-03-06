#include "Renderer.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "SDLStruct.hpp"

Renderer::Renderer(SDL_Renderer* renderer)
{
	ptr = shared_ptr<SDL_Renderer>(renderer, [=](SDL_Renderer* p) { if (p) SDL_DestroyRenderer(p); STDLOG << "Renderer Destroyed"; });
	if (!ptr) throw RenderException();
}

void Renderer::Clear()
{
	if (SDL_RenderClear(ptr.get()))
		throw RenderException();
}

void Renderer::Present()
{
	SDL_RenderPresent(ptr.get());
}

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
	if (SDL_SetRenderDrawColor(ptr.get(), r, g, b, alpha))
		throw RenderException();
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

void Renderer::CopyEx(Texture const& texture, Rect const& from, Rect const& to, double angle, Point const& center, SDL_RendererFlip flip)
{
	copyEx(texture, &from, &to, angle, &center, flip);
}

void Renderer::CopyEx(Texture const& texture, Rect const& from, Rect const& to, double angle, SDL_RendererFlip flip)
{
	copyEx(texture, &from, &to, angle, nullptr, flip);
}

Texture Renderer::CreateFromSurface(Surface const & surface)
{
	return Texture(SDL_CreateTextureFromSurface(ptr.get(), surface.ptr.get()));
}

Texture Renderer::LoadTexture(string const & path)
{
	return CreateFromSurface(Surface::LoadIMG(path));
}

void Renderer::copy(Texture const & texture, const Rect * from, const Rect * to)
{
	const SDL_Rect *src, *dst;
	src = dst = nullptr;
	if (from) src = &from->data;
	if (to) dst = &to->data;
	if (SDL_RenderCopy(ptr.get(), texture.ptr.get(), src, dst))
		throw RenderException();
}

void Renderer::copyEx(Texture const& texture, const Rect* from, const Rect* to, double angle, const Point* center, SDL_RendererFlip flip)
{
	const SDL_Rect *src, *dst;
	const SDL_Point* cntr = nullptr;
	src = dst = nullptr;
	if (from) src = &from->data;
	if (to) dst = &to->data;
	if (center) cntr = &center->data;
	if (SDL_RenderCopyEx(ptr.get(), texture.ptr.get(), src, dst, angle, cntr, flip))
		throw RenderException();
}
