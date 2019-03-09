#pragma once

#include "Common.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"

class Renderer;

class Renderable {
public:
	Renderable() = delete;
	Renderable(Renderable const&) = delete;
	void operator=(Renderable const&) = delete;

	Renderable(string const& id, Texture const& texture, Position const& pos, Size const& size = Size(0), SDL_RendererFlip flip = SDL_FLIP_NONE)
		: id(id), texture(texture), pos(pos), size(size), flip(flip), shown(true) {}
	virtual ~Renderable() = default;

	virtual void draw(Renderer& renderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

	bool isShown() { return shown; }
	void show() { shown = true; }
	void hide() { shown = false; }
	void setSize(Size const& s) { size = s; }
	void setFlip(SDL_RendererFlip f) { flip = f; }
protected:
	string id;
	Texture texture;
	Position pos;
	Size size;
	SDL_RendererFlip flip;
	bool shown;
};
