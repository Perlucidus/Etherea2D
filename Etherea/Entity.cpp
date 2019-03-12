#include "Entity.hpp"
#include "Renderer.hpp"
#include <algorithm>

Entity::Entity(string const& id, Texture const& texture, Position const& pos, Size const& size,
	Size const& frameSize, float base_speed, SDL_RendererFlip flip)
	: Animated(id, texture, size, AnimationFrame(frameSize), base_speed, flip),
	position(pos), moving(false), velocity(0), gravity(0), last_move(SDL_GetTicks()) {}

Direction Entity::getFacingDirection() const
{
	return facing;
}

bool Entity::isMoving() const
{
	return moving;
}

void Entity::face(Direction const& d)
{
	facing = (d != Direction(0)) ? d.normalized() : d;
}

void Entity::setMoving(bool set)
{
	moving = set;
	if (!set) setVelocity(getVelocity() * Velocity(0, 1));
}

bool Entity::isAirborne() const
{
	return airborne;
}

void Entity::setAirborne(bool set)
{
	airborne = set;
	if (!set) setVelocity(getVelocity() * Velocity(1, 0));
}

Velocity Entity::getVelocity() const
{
	return velocity;
}

void Entity::setVelocity(Velocity const& v)
{
	velocity = v;
	setAnimationSpeed(base_speed * std::abs(v.x));
}

Velocity Entity::getGravity() const
{
	return gravity;
}

void Entity::setGravity(Velocity const& g)
{
	gravity = g;
}

void Entity::draw(Renderer& renderer)
{
	if (!shown)
		return;
	Rectangle src(static_cast<Position>(size * getAnimationFrame().getFrame()), size), dst(position, size);
	Uint32 f = flip;
	if (facing.x < 0) f ^= SDL_FLIP_HORIZONTAL;
	if (facing.y < 0) f ^= SDL_FLIP_VERTICAL;
	double rads;
	if (facing.x == 0)
		rads = facing.y * M_PI / 2;
	else
		rads = atan(static_cast<double>(facing.y) / facing.x);
	renderer.CopyEx(texture, src, dst, rads / M_PI * 180., static_cast<SDL_RendererFlip>(f));
}
