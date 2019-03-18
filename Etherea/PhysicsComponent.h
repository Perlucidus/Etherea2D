#pragma once

#include "EntityComponent.hpp"
#include "Vector2D.hpp"

class PhysicsComponent : public EntityComponent {
public:
	PhysicsComponent(Size const& hitbox) : hitbox(hitbox) {}

	Size getHitbox() const { return hitbox; }
	void setHitbox(Size const& size) { hitbox = size; }
private:
	Size hitbox;
};
