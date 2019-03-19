#pragma once

class Renderer;

class IGameObject {
public:
	virtual ~IGameObject() = default;

	virtual void update() = 0;
	virtual void render(Renderer& renderer) = 0;
};
