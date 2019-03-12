#pragma once

#include "Renderable.hpp"

class AnimationFrame {
public:
	AnimationFrame() = delete;
	AnimationFrame(Size const& size, Size const& current = Size(0));

	void set(Size const& frame);

	void advance(Size const& offset);

	Size const& getSize() const;
	Size const& getFrame() const;
private:
	Size size, current;
};

class Animated : public Renderable {
public:
	Animated() = delete;
	Animated(Animated const&) = delete;
	void operator=(Animated const&) = delete;

	Animated(string const& id, Texture const& texture, Position const& pos, Size const& size,
		AnimationFrame const& frame, float base_speed, SDL_RendererFlip flip = SDL_FLIP_NONE);
	virtual ~Animated() = default;

	virtual void update() override;

	bool canAnimate() const;
	float getAnimationSpeed() const;
	void setAnimationSpeed(float speed);
	AnimationFrame const& getAnimationFrame() const;
	void setFrame(Size const& size);
	void advanceFrame(Size const& offset);
protected:
	float base_speed, animation_speed; //animations/second
private:
	AnimationFrame frame;
	double prev_update;
};
