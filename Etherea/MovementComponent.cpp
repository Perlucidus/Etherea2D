#include "MovementComponent.hpp"
#include "Game.hpp"

MovementComponent::MovementComponent(Velocity const& velocity) : velocity(velocity), last_movement_time(GAME.GetTicks()) {}

Velocity MovementComponent::getVelocity() const
{
	return velocity;
}

void MovementComponent::setVelocity(Velocity const & v)
{
	velocity = v;
}

Position MovementComponent::getMovementDistance() const
{
	return velocity * static_cast<float>((GAME.GetTicks() - last_movement_time) / 1000);
}

void MovementComponent::updateMovementTimer()
{
	last_movement_time = GAME.GetTicks();
}
