#pragma once

#include "Renderable.hpp"

class Entity : public IAnimated {
public:
	Entity() = delete;
	Entity(string const& id, Rect const& rect, size_t row_size, size_t column_size, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Inherited via IRenderable
	virtual void draw(Renderer & renderer) override;
	virtual void update() override;
	virtual void clean() override;
};
