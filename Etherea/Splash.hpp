#pragma once

#include "Entity.hpp"
#include "GameComponent.hpp"
#include "RenderComponent.hpp"
#include "Game.hpp"

class Splash : public Entity {
public:
	Splash();

	// Inherited via Renderable
	virtual void draw(Renderer & renderer) override;
	virtual void update() override;
	virtual void clean() override {}

	void setProgress(float p);
private:
	float progress;
};

class SplashScreen : public GameComponent {
public:
	SplashScreen();

	virtual void initialize() override;
	virtual void update() override;
	virtual void render(Renderer& renderer) override;
	virtual void clean() override {}
private:
	static TimerResult end(Uint32 interval, void* param);
private:
	Timer timer;
	Uint32 start;
	Splash splash;
};

class SplashEventHandler : public EventHandler {
public:
	// Inherited via EventHandler
	virtual bool handle(SDL_Event const& event) override;
};
