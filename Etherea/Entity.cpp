#include "Entity.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"

Entity::Entity(string const& id, Position const& pos, Size const& size,
	Size const& frameSize, Uint32 base_fps, SDL_RendererFlip flip, Velocity velocity)
	: IAnimated(id, pos, size, AnimationFrame(frameSize), base_fps, flip), moving(false), velocity(velocity) {}

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
	SDL_RendererFlip f = flip;
	if (facing.getX() < 0)
		f = static_cast<SDL_RendererFlip>(f ^ SDL_FLIP_HORIZONTAL);
	if (facing.getY() < 0)
		f = static_cast<SDL_RendererFlip>(f ^ SDL_FLIP_VERTICAL);
	TextureManager::getInstance(renderer).Draw(id, pos, size, frame.getFrame(), f);
}
