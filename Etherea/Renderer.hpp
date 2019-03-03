#pragma once

#include "Common.hpp"

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
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha = SDL_ALPHA_OPAQUE);

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
