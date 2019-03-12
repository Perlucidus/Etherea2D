#include "Animated.hpp"
#include "Game.hpp"

AnimationFrame::AnimationFrame(Size const& size, Size const& current) : size(size), current(current) {}

void AnimationFrame::set(Size const& frame)
{
	current = frame;
}

void AnimationFrame::advance(Size const& offset)
{
	current += offset;
	current = Size(current.x % size.x, current.y % size.y);
}

Size const& AnimationFrame::getSize() const
{
	return size;
}

Size const& AnimationFrame::getFrame() const
{
	return current;
}

Animated::Animated(string const& id, Texture const& texture, Size const& size,
	AnimationFrame const & frame, float base_speed, SDL_RendererFlip flip)
	: Renderable(id, texture, size, flip), frame(frame), prev_update(0),
	base_speed(base_speed), animation_speed(base_speed) {}

void Animated::update()
{
	if (canAnimate())
		prev_update = GAME.GetTicks();
}

bool Animated::canAnimate() const
{
	return (GAME.GetTicks() - prev_update) >= 1000.f / animation_speed;
}

float Animated::getAnimationSpeed() const
{
	return animation_speed;
}

void Animated::setAnimationSpeed(float speed)
{
	animation_speed = speed;
}

AnimationFrame const& Animated::getAnimationFrame() const
{
	return frame;
}

void Animated::setFrame(Size const& size)
{
	frame.set(size);
}

void Animated::advanceFrame(Size const & offset)
{
	if (canAnimate())
		frame.advance(offset);
}
