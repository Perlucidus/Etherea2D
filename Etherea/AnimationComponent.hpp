#pragma once

#include "EntityComponent.hpp"
#include "Vector2D.hpp"

class Rectangle;

class AnimationComponent : public EntityComponent {
public:
	AnimationComponent(Size const& count, Size const& size, float speed = 0, Size const& frame = Size(0));

	Size getCurrentFrame() const;
	Size getFrameCount() const;
	Size getFrameSize() const;
	Rectangle getFrameRectangle() const;
	bool canAnimate() const;
	void setCurrentFrame(Size const& frame);
	void cycleColumn();
	void cycleRow();
	void setAnimationSpeed(float speed);
	void updateAnimationTimer();
private:
	Size current_frame, frame_count, frame_size;
	float animation_speed;
	double last_animation_time;
};
