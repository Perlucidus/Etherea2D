#pragma once

#include "Entity.hpp"
#include "TextureManager.hpp"
#include "PixelFormat.hpp"

//////////////////////////////
//	For Testing Purposes	//
//////////////////////////////

class Snek : public Entity {
public:
	Snek() : Entity("snake", Position(), Size(134, 134), Size(4, 1), 10, SDL_FLIP_HORIZONTAL, Velocity(10, 0)),
		mod(Color(255, 255, 255))
	{
		facing = Direction(1, 0);
	}

	void changeColor(SDL_Color color) {
		mod = color;
	}

	// Inherited via Entity
	void draw(Renderer& renderer)
	{
		Texture& texture = TextureManager::getInstance(renderer).GetTexture(id);
		texture.ColorMod(mod);
		Entity::draw(renderer);
	}

	void update()
	{
		if (!canUpdate())
			return;
		if (moving) {
			pos += facing * velocity;
			frame++;
		}
		else
			frame.set(Size(3, 0)); //Standing
		Entity::update();
	}

	void clean() {}
private:
	SDL_Color mod;
};
