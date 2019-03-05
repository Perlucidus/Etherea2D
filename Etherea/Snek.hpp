#pragma once

#include "Entity.hpp"

//////////////////////////////
//	For Testing Purposes	//
//////////////////////////////

class Snek : public Entity {
public:
	Snek() : Entity("snake", Position(), Size(134, 134), Size(4, 1), 10, SDL_FLIP_HORIZONTAL, Velocity(5, 0)) {}

	// Inherited via Entity
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
};
