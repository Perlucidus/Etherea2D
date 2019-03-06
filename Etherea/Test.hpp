#pragma once

#include "Entity.hpp"
#include "TextureManager.hpp"

//////////////////////////////
//	For Testing Purposes	//
//////////////////////////////

class Snek : public Entity {
public:
	Snek() : Entity("snake", Position(), Size(134, 134), Size(4, 1), 10, SDL_FLIP_HORIZONTAL, Velocity(10, 0)),
		rmod(255), gmod(255), bmod(255)
	{
		facing = Direction(1, 0);
	}

	void changeColor(Uint8 r, Uint8 g, Uint8 b) {
		rmod = r;
		gmod = g;
		bmod = b;
	}

	// Inherited via Entity
	void draw(Renderer& renderer)
	{
		TextureManager::getInstance(renderer).GetTexture(id).ColorMod(rmod, gmod, bmod);
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
	Uint8 rmod, gmod, bmod;
};
