#pragma once

#include "Renderable.hpp"

class Entity : public IAnimated {
public:
	Entity() = delete;
	Entity(string const& id, Position const& pos, Size const& size, Size const& frameSize, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Inherited via IRenderable
	virtual void draw(Renderer & renderer) override;
	virtual void update() override;
	virtual void clean() override;
};
