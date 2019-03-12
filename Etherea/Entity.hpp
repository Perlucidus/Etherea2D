#pragma once

#include "Animated.hpp"

class Entity : public Animated {
public:
	Entity() = delete;
	Entity(Entity const&) = delete;
	void operator=(Entity const&) = delete;

	Entity(string const& id, Texture const& texture, Position const& pos, Size const& size, Size const& frameSize,
		float base_speed, SDL_RendererFlip flip = SDL_FLIP_NONE);

	Direction getFacingDirection() const;
	bool isMoving() const;
	void face(Direction const& d);
	void setMoving(bool set);
	bool isAirborne() const;
	void setAirborne(bool set);
	Velocity getVelocity() const;
	void setVelocity(Velocity const& v);
	Velocity getGravity() const;
	void setGravity(Velocity const& g);

	// Inherited via Renderable
	virtual void draw(Renderer & renderer) override;
protected:
	Direction facing;
	double last_move;
	bool moving;
	bool airborne;
	Velocity velocity; //pixels/(animations/10ms)
	Velocity gravity;
};
