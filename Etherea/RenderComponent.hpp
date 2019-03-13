#pragma once

#include "EntityComponent.hpp"
#include "Texture.hpp"
#include "Geometry.hpp"

class RenderComponent : public EntityComponent {
public:
	RenderComponent(Texture const& t);
	RenderComponent(Texture const& texture, Size const& size);

	Texture& getTexture();
	Size const& getTextureSize() const;
	double getRenderAngle() const;
	Point const& getRotationCenter() const;
	SDL_RendererFlip getFlip() const;
	void setTexture(Texture const& t);
	void setTextureSize(Size const& size);
	void setRenderAngle(double angle);
	void setRotationCenter(Point const& center);
	void setFlip(SDL_RendererFlip f);
private:
	Texture texture;
	Size texture_size;
	double render_angle;
	Point rotation_center;
	SDL_RendererFlip flip;
};
