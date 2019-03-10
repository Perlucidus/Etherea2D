#pragma once

#include "Renderable.hpp"
#include "Game.hpp"

class Splash : public Renderable {
public:
	Splash(Texture const& texture, Uint32 delay);

	// Inherited via Renderable
	virtual void draw(Renderer & renderer) override;
	virtual void update() override;
	virtual void clean() override;
private:
	static TimerResult end(Uint32 interval, void* param);
private:
	Timer timer;
	Uint32 start;
};

class SplashScreen : public GameComponent {
public:
	SplashScreen();
};

class SplashEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual void Handle(SDL_Event const& event) override;
};
