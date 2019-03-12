#pragma once

#include "Entity.hpp"
#include "GameComponent.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"
#include "Random.hpp"

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
	Texture t, t120l, t120r;
	const Velocity v;
	size_t mode;
	SDL_Color mod;
	int angle;
};

class TestComponent : public GameComponent {
public:
	TestComponent() = default;

	virtual void Init() override;
};

class TestEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
private:
	void KeyEvent(Uint8 const* state);
};
