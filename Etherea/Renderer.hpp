#pragma once

#include "Common.hpp"
#include "Exception.hpp"
#include "Geometry.hpp"
#include <SDL_render.h>
 
class Surface;
class Texture;

class Renderer {
public:
	Renderer();
	explicit Renderer(SDL_Renderer* renderer);
	virtual ~Renderer() = default;

	void SetScreenPosition(Position const& pos);
	void SetScreenSize(Size const& size);

	void Clear();
	void Present();
	void SetDrawColor(SDL_Color const& color);
	void SetTarget(Texture const& texture);
	void ClearTarget();

	void DrawPoint(Point const& point);
	void DrawLine(Point const& p1, Point const& p2);
	void DrawRectangle(Rectangle const& rect);
	void DrawCircle(Point const& center, uint16_t radius);
	void Copy(Texture const& texture, Rectangle const& from, Rectangle const& to);
	void CopyFrom(Texture const& texture, Rectangle const& from);
	void CopyTo(Texture const& texture, Rectangle const& to);
	void CopyEx(Texture const& texture, Rectangle const& from, Rectangle const& to, double angle,
				Point const& center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void CopyEx(Texture const& texture, Rectangle const& from, Rectangle const& to, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	Texture CreateFromSurface(Surface const& surface);
	Texture LoadTexture(string const& path);
private:
	void copy(Texture const& texture, const Rectangle* from = nullptr, const Rectangle* to = nullptr);
	void copyEx(Texture const& texture, const Rectangle* from = nullptr, const Rectangle* to = nullptr,
			  double angle = 0, const Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	shared_ptr<SDL_Renderer> ptr;
	Rectangle screen;
};

class RenderException : public SDLException {};
