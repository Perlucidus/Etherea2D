#include "RenderComponent.hpp"

RenderComponent::RenderComponent(Texture const& t) : texture(t), texture_size(0)
{
	if (t.isLoaded())
		texture.Query(texture_size);
}

RenderComponent::RenderComponent(Texture const & texture, Size const & size) :
	texture(texture), texture_size(size), render_angle(0),
	rotation_center(static_cast<Position>(size) / 2), flip(SDL_FLIP_NONE) {}

Texture& RenderComponent::getTexture()
{
	return texture;
}

Size const& RenderComponent::getTextureSize() const
{
	return texture_size;
}

double RenderComponent::getRenderAngle() const
{
	return render_angle;
}

Point const& RenderComponent::getRotationCenter() const
{
	return rotation_center;
}

SDL_RendererFlip RenderComponent::getFlip() const
{
	return flip;
}

void RenderComponent::setTexture(Texture const & t)
{
	texture = t;
}

void RenderComponent::setTextureSize(Size const & size)
{
	texture_size = size;
}

void RenderComponent::setRenderAngle(double angle)
{
	if (angle < 0 || angle >= 360)
		throw std::logic_error("Invalid angle");
	render_angle = angle;
}

void RenderComponent::setRotationCenter(Point const& center)
{
	rotation_center = center;
}

void RenderComponent::setFlip(SDL_RendererFlip f)
{
	flip = f;
}
