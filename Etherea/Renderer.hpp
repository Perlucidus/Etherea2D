#pragma once

#include "Common.hpp"
#include "PixelFormat.hpp"
 
class Surface;
class Texture;
class Rect;
class Point;

class Renderer {
public:
	Renderer() = default;
	explicit Renderer(SDL_Renderer* renderer);
	virtual ~Renderer() = default;

	void Clear();
	void Present();
	void SetDrawColor(SDL_Color const& color);
	void SetTarget(Texture const& texture);
	void ClearTarget();

	void Copy(Texture const& texture, Rect const& from, Rect const& to);
	void CopyFrom(Texture const& texture, Rect const& from);
	void CopyTo(Texture const& texture, Rect const& to);
	void CopyEx(Texture const& texture, Rect const& from, Rect const& to, double angle,
				Point const& center, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void CopyEx(Texture const& texture, Rect const& from, Rect const& to, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	Texture CreateFromSurface(Surface const& surface);
	Texture LoadTexture(string const& path);
private:
	void copy(Texture const& texture, const Rect* from = nullptr, const Rect* to = nullptr);
	void copyEx(Texture const& texture, const Rect* from = nullptr, const Rect* to = nullptr,
			  double angle = 0, const Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	shared_ptr<SDL_Renderer> ptr;
};
