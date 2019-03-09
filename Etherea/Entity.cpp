#include "Entity.hpp"
#include "Renderer.hpp"
#include "SDLStruct.hpp"

Entity::Entity(string const& id, Texture const& texture, Position const& pos, Size const& size,
	Size const& frameSize, Uint32 base_fps, SDL_RendererFlip flip, Velocity velocity)
	: Animated(id, texture, pos, size, AnimationFrame(frameSize), base_fps, flip), moving(false), velocity(velocity) {}

Direction Entity::getFacingDirection() const
{
	return facing;
}

bool Entity::isMoving() const
{
	return moving;
}

void Entity::setFacingDirection(Direction const& d)
{
	facing = d ? d.normalized() : d;
}

void Entity::setMoving(bool move)
{
	moving = move;
}

Velocity Entity::getVelocity() const
{
	return velocity;
}

void Entity::setVelocity(Velocity v)
{
	velocity = v;
}

void Entity::draw(Renderer& renderer)
{
	if (!shown)
		return;
	Uint32 f = flip;
	if (facing.getX() < 0) f ^= SDL_FLIP_HORIZONTAL;
	if (facing.getY() < 0) f ^= SDL_FLIP_VERTICAL;
	Rect src(static_cast<Position>(size * frame.getFrame()), size), dst(pos, size);
	renderer.CopyEx(texture, src, dst, 0, static_cast<SDL_RendererFlip>(f));
}
