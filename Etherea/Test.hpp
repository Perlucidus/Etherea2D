#pragma once

#include "Entity.hpp"
#include "RenderComponent.hpp"
#include "AnimationComponent.hpp"
#include "FaceComponent.hpp"
#include "GravityComponent.hpp"
#include "LocationComponent.hpp"
#include "MovementComponent.hpp"
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
	void setVelocity(Velocity velocity);
public:
	RenderComponent render;
	AnimationComponent animation;
	FaceComponent face;
	LocationComponent location;
	MovementComponent movement;
	GravityComponent gravity;

	Texture t, t120l, t120r;
	const Velocity v;
	const float s;
	size_t mode;
	SDL_Color mod;
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
