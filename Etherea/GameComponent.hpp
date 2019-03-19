#pragma once

#include "IGameObject.hpp"
#include "Renderer.hpp"

class GameComponent : public IGameObject {
public:
	GameComponent() = default;
	virtual ~GameComponent() = default;
	GameComponent(GameComponent const&) = delete;
	void operator=(GameComponent const&) = delete;

	virtual void initialize() = 0;
};
