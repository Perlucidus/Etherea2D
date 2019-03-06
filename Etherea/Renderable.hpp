#pragma once

#include "Common.hpp"
#include "Vector2D.hpp"

class Renderer;

class Renderable {
public:
	Renderable() = delete;

	Renderable(string const& id, Position const& pos, Size const& size = Size(0), SDL_RendererFlip flip = SDL_FLIP_NONE)
		: id(id), shown(true), pos(pos), size(size), flip(flip) {}
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
	bool shown;
	Position pos;
	Size size;
	SDL_RendererFlip flip;
};
