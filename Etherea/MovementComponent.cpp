#include "MovementComponent.hpp"
#include "Game.hpp"

const int MAX_PIXEL_PER_TICK = 7; //Makes collision testing easier for up to 1-tile (16px) entities
const float MAX_VELOCITY = static_cast<float>(MAX_PIXEL_PER_TICK * (1000. / Game::TICK_RATE));

MovementComponent::MovementComponent(Velocity const& velocity) : velocity(velocity), last_movement_time(GAME.GetTicks()) {}

Velocity MovementComponent::getVelocity() const
{
	return velocity;
}

void MovementComponent::setVelocity(Velocity const & v)
{
	velocity = Velocity(std::fminf(v.x, MAX_VELOCITY), std::fminf(v.y, MAX_VELOCITY));
}

Position MovementComponent::getMovementDistance() const
{
	return velocity * static_cast<float>((GAME.GetTicks() - last_movement_time) / 1000);
}

void MovementComponent::updateMovementTimer()
{
	last_movement_time = GAME.GetTicks();
}
