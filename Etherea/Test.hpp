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
	Snek(Texture const& texture);

	void changeColor(SDL_Color color);

	// Inherited via Entity
	virtual void draw(Renderer& renderer) override;
	virtual void update() override;
	virtual void clean() override;
private:
	SDL_Color mod;
};

class TestComponent : public GameComponent {
public:
	TestComponent();
};

class TestEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
private:
	void KeyEvent(Uint8 const* state);
	void KeyDown(SDL_KeyboardEvent const& event);
	void KeyUp(SDL_KeyboardEvent const& event);
	Direction GetKeyDirection(SDL_Keycode key, Snek& player);
};
