#include "AnimationComponent.hpp"
#include "Geometry.hpp"
#include "Game.hpp"

AnimationComponent::AnimationComponent(Size const& count, Size const& size, float speed, Size const& frame) :
	current_frame(frame), frame_count(count), frame_size(size), animation_speed(speed)
{
	if (frame.x > (count.x - 1) || frame.y > (count.y - 1))
		throw std::logic_error("Animation frame out of bounds");
}

Size AnimationComponent::getCurrentFrame() const
{
	return current_frame;
}

Size AnimationComponent::getFrameCount() const
{
	return frame_count;
}

Size AnimationComponent::getFrameSize() const
{
	return frame_size;
}

Rectangle AnimationComponent::getFrameRectangle() const
{
	return Rectangle(static_cast<Position>(frame_size * current_frame), frame_size);
}

bool AnimationComponent::canAnimate() const
{
	return (animation_speed > 0) && (((GAME.GetTicks() - last_animation_time) / 1000) >= (1 / animation_speed));
}

void AnimationComponent::setCurrentFrame(Size const & frame)
{
	if (frame.x > (frame_count.x - 1) || frame.y > (frame_count.y - 1))
		throw std::logic_error("Animation frame out of bounds");
	current_frame = frame;
}

void AnimationComponent::cycleColumn()
{
	current_frame.x = (current_frame.x + 1) % frame_count.x;
}

void AnimationComponent::cycleRow()
{
	current_frame.y = (current_frame.y + 1) % frame_count.y;
}

void AnimationComponent::setAnimationSpeed(float speed)
{
	if (speed < 0)
		throw std::logic_error("Negative animation speed");
	animation_speed = speed;
}

void AnimationComponent::updateAnimationTimer()
{
	last_animation_time = GAME.GetTicks();
}
