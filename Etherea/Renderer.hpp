#pragma once

#include "Common.hpp"
#include "SDLComponent.hpp"

class Surface;
class Texture;
class Rect;

class Renderer : public SDLComponent {
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
	Texture CreateFromSurface(Surface const& surface);
	Texture LoadTextureImg(string const& path);
private:
	void copy(Texture const& texture, const Rect* from = nullptr, const Rect* to = nullptr);
private:
	shared_ptr<SDL_Renderer> ptr;
};
