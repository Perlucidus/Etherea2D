#pragma once

#include "Renderer.hpp"

class GameComponent {
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;
	GameComponent(GameComponent const&) = delete;
	void operator=(GameComponent const&) = delete;

	virtual void initialize() = 0;

	virtual void update() = 0;
	virtual void render(Renderer& renderer) = 0;
	virtual void clean() = 0;
};
