#include "Renderer.hpp"
#include "Surface.hpp"
#include "Texture.hpp"

Renderer::Renderer() : ptr(nullptr) {}

Renderer::Renderer(SDL_Renderer* renderer)
{
	ptr = shared_ptr<SDL_Renderer>(renderer, [=](SDL_Renderer* p) { if (p) SDL_DestroyRenderer(p); STDLOG << "Renderer Destroyed"; });
	if (!ptr) throw RenderException();
}

void Renderer::SetScreenPosition(Position const& pos)
{
	screen.tl = Point(pos);
}

void Renderer::SetScreenSize(Size const& size)
{
	screen.setSize(static_cast<Position::Type>(size.x), static_cast<Position::Type>(size.y));
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

void Renderer::SetDrawColor(SDL_Color const& color)
{
	if (SDL_SetRenderDrawColor(ptr.get(), color.r, color.g, color.b, color.a))
		throw RenderException();
}

void Renderer::SetTarget(Texture const& texture)
{
	if (SDL_SetRenderTarget(ptr.get(), texture.ptr.get()))
		throw RenderException();
}

void Renderer::ClearTarget()
{
	if (SDL_SetRenderTarget(ptr.get(), nullptr))
		throw RenderException();
}

void Renderer::DrawPoint(Point const & point)
{
	if (SDL_RenderDrawPoint(ptr.get(), static_cast<int>(point->x), static_cast<int>(point->y)))
		throw RenderException();
}

void Renderer::DrawLine(Point const & p1, Point const & p2)
{
	if (SDL_RenderDrawLine(ptr.get(), static_cast<int>(p1->x), static_cast<int>(p1->y),
		static_cast<int>(p2->x), static_cast<int>(p2->y)))
		throw RenderException();
}

void Renderer::DrawRectangle(Rectangle const & rect)
{
	if (SDL_RenderDrawRect(ptr.get(), &rect.ToSDLRect()))
		throw RenderException();
}

void Renderer::Copy(Texture const& texture, Rectangle const & from, Rectangle const & to)
{
	copy(texture, &from, &to);
}

void Renderer::CopyFrom(Texture const & texture, Rectangle const & from)
{
	copy(texture, &from);
}

void Renderer::CopyTo(Texture const & texture, Rectangle const & to)
{
	copy(texture, nullptr, &to);
}

void Renderer::CopyEx(Texture const& texture, Rectangle const& from, Rectangle const& to, double angle, Point const& center, SDL_RendererFlip flip)
{
	copyEx(texture, &from, &to, angle, &center, flip);
}

void Renderer::CopyEx(Texture const& texture, Rectangle const& from, Rectangle const& to, double angle, SDL_RendererFlip flip)
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

void Renderer::copy(Texture const & texture, const Rectangle * from, const Rectangle * to)
{
	if (to && !to->overlaps(screen))
		return;
	const SDL_Rect *src, *dst;
	src = dst = nullptr;
	if (from) src = &from->ToSDLRect();
	if (to) dst = &to->ToSDLRect();
	if (SDL_RenderCopy(ptr.get(), texture.ptr.get(), src, dst))
		throw RenderException();
}

void Renderer::copyEx(Texture const& texture, const Rectangle* from, const Rectangle* to, double angle, const Point* center, SDL_RendererFlip flip)
{
	if (to && !to->overlaps(screen))
		return;
	const SDL_Rect *src, *dst;
	const SDL_Point* cntr = nullptr;
	src = dst = nullptr;
	if (from) src = &from->ToSDLRect();
	if (to) dst = &to->ToSDLRect();
	if (center) cntr = &center->ToSDLPoint();
	if (SDL_RenderCopyEx(ptr.get(), texture.ptr.get(), src, dst, angle, cntr, flip))
		throw RenderException();
}
