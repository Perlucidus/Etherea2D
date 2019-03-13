#pragma once

#include "EntityComponent.hpp"
#include "Vector2D.hpp"

class MovementComponent : public EntityComponent {
public:
	MovementComponent(Velocity const& velocity = Velocity(0));

	Velocity getVelocity() const;
	void setVelocity(Velocity const& v);
	Position getMovementDistance() const;
	void updateMovementTimer();
private:
	Velocity velocity;
	double last_movement_time;
};
