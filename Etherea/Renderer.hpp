#pragma once

#include "Common.hpp"
#include "Window.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Rect.hpp"

class Renderer : public SDLComponent {
public:
	Renderer() = delete;

	Renderer(Window* window, int index, Uint32 flags);
	Renderer(Window* window, Uint32 flags);
	virtual ~Renderer();

	void Clear();
	void Present();
	void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha = SDL_ALPHA_OPAQUE);

	void Copy(Texture const& texture, Rect const& from, Rect const& to);
	void CopyFrom(Texture const& texture, Rect const& from);
	void CopyTo(Texture const& texture, Rect const& to);
	Texture CreateFromSurface(Surface const& surface);
private:
	void copy(Texture const& texture, const Rect* from = nullptr, const Rect* to = nullptr);
private:
	SDL_Renderer* ptr;
	Window* window;
};
