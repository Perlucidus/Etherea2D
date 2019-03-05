#include "Entity.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"

Entity::Entity(string const& id, Position const& pos, Size const& size, Size const& frameSize, SDL_RendererFlip flip)
	: IAnimated(id, pos, size, AnimationFrame(frameSize), flip) {}

void Entity::draw(Renderer& renderer)
{
	TextureManager::getInstance(renderer).Draw(id, pos, size, frame.getFrame(), flip);
}

void Entity::update()
{
	frame.advance(1, 0);
}

void Entity::clean()
{
}
