#pragma once

#include "EntityComponent.hpp"
#include "Vector2D.hpp"

class FaceComponent : public EntityComponent {
public:
	FaceComponent(Direction const& direction) : face_direction(direction) {}

	Direction getFacingDirection() const
	{
		return face_direction;
	}

	void face(Direction const& direction)
	{
		if (direction == Direction(0))
			throw std::logic_error("Directionless vector");
		face_direction = direction.normalized();
	}
private:
	Direction face_direction;
};
