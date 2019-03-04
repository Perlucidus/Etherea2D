#include "Entity.hpp"
#include "Renderer.hpp"
#include "TextureManager.hpp"

Entity::Entity(string const& id, Rect const& rect, size_t row_size, size_t col_size, SDL_RendererFlip flip)
	: IAnimated(id, rect, AnimationFrame(row_size, col_size), flip) {}

void Entity::draw(Renderer& renderer)
{
	TextureManager::getInstance(renderer).Draw(id, rect, frame.getRow(), frame.getColumn(), flip);
}

void Entity::update()
{
	frame.advance(1, 0);
}

void Entity::clean()
{
}
