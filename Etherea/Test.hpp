#pragma once

#include "Entity.hpp"
#include "GameComponent.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"
#include "World.hpp"

//////////////////////////////
//	For Testing Purposes	//
//////////////////////////////

class Snek : public Entity {
public:
	Snek();

	// Inherited via Entity
	virtual void draw(Renderer& renderer) override;
	virtual void update() override;
	virtual void clean() override;
public:
	void setVelocity(Velocity velocity);
public:
	Texture t, t120l, t120r;
	const Velocity v;
	const float s;
	size_t mode;
	SDL_Color mod;
};

class Plant : public Entity {
public:
	Plant(string const& id);

	// Inherited via Entity
	virtual void draw(Renderer & renderer) override;
	virtual void update() override;
	virtual void clean() override;
public:
	Texture t, t120l, t120r;
};

class TestWorld : public World {
public:
	TestWorld() = default;

	// Inherited via World
	virtual void initialize() override;
	virtual void update() override;
};

class TestEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual bool handle(SDL_Event const& event) override;
private:
	void KeyEvent(Uint8 const* state);
};
