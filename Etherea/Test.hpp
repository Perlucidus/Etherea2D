#pragma once

#include "Entity.hpp"
#include "GameComponent.hpp"
#include "SoundManager.hpp"
#include "Splash.hpp"

//////////////////////////////
//	For Testing Purposes	//
//////////////////////////////

class Snek : public Entity {
public:
	Snek(Texture const& texture) : Entity("snake", texture, Position(), Size(134, 134), Size(4, 1), 10, SDL_FLIP_HORIZONTAL, Velocity(10, 0)),
		mod(Color(255, 255, 255))
	{
		facing = Direction(1, 0);
	}

	void changeColor(SDL_Color color) {
		mod = color;
	}

	// Inherited via Entity
	void draw(Renderer& renderer)
	{
		texture.ColorMod(mod);
		Entity::draw(renderer);
	}

	void update()
	{
		if (!canUpdate())
			return;
		if (moving) {
			pos += facing * velocity;
			frame++;
		}
		else
			frame.set(Size(3, 0)); //Standing
		Entity::update();
	}

	void clean() {}
private:
	SDL_Color mod;
};

class TestComponent : public GameComponent {
public:
	TestComponent() {
		SoundManager& sm = SoundManager::getInstance();
		sm.LoadMusic("../assets/sound/The Builder.mp3");
		sm.SetMusicVolume(0.01f);
		sm.PlayMusic(LOOP_SOUND_FOREVER, 500);
		AddObject("splash", make_unique<Splash>(GAME.GetRenderer().LoadTexture("../assets/textures/splash.png"), 2000));
		AddObject("player", make_unique<Snek>(GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png")));
		GetObject<Snek>("player").hide();
	}
};
