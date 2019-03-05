#pragma once

#include "Renderable.hpp"

class Entity : public IAnimated {
public:
	Entity() = delete;
	Entity(string const& id, Position const& pos, Size const& size, Size const& frameSize,
		Uint32 base_fps, SDL_RendererFlip flip = SDL_FLIP_NONE, Velocity velocity = Velocity(0));

	Direction getFacingDirection() const;
	bool isMoving() const;
	void setFacingDirection(Direction const& d);
	void setMoving(bool moving);
	Velocity getVelocity() const;
	void setVelocity(Velocity v);

	// Inherited via IRenderable
	virtual void draw(Renderer & renderer) override;
protected:
	Direction facing;
	bool moving;
	Velocity velocity;
};
