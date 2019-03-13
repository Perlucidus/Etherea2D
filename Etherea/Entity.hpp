#pragma once

#include "Renderer.hpp"

class Entity {
public:
	Entity() = delete;
	Entity(Entity const&) = delete;
	void operator=(Entity const&) = delete;

	explicit Entity(string const& id) : id(id) {}

	virtual void draw(Renderer & renderer) = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
protected:
	string id;
};
