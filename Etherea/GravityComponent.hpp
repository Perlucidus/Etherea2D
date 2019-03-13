#pragma once

#include "EntityComponent.hpp"
#include "Vector2D.hpp"

class GravityComponent : public EntityComponent {
public:
	GravityComponent(Velocity::Type gravity) : gravity(gravity) {}

	Velocity::Type getGravity() const { return gravity; }
	void setGravity(Velocity::Type g) { gravity = g; }
private:
	Velocity::Type gravity;
};
