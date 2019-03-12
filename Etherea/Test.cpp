#include "Test.hpp"

Snek::Snek() : Entity("snake", Texture(), Position(), Size(134, 134), Size(4, 1),
	0.1f, SDL_FLIP_HORIZONTAL), v(Velocity(100, 100)), mode(0), mod(Color(255, 255, 255))
{
	texture = t = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png");
	t120l = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120l.png");
	t120r = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120r.png");
	facing = Direction(1, 0);
}

void Snek::draw(Renderer & renderer)
{
	texture.ColorMod(mod);
	Entity::draw(renderer);
}

void Snek::update()
{
	float dt = static_cast<float>((GAME.GetTicks() - last_move) / 1000);
	if (moving || airborne) {
		pos += getVelocity() * dt;
		if (airborne) {
			setFrame(Size(3, 0)); //Jumping
			setVelocity(getVelocity() + gravity * dt);
		}
		else advanceFrame(Size(1, 0));
	}
	else setFrame(Size(3, 0)); //Standing
	last_move = GAME.GetTicks();
	Entity::update();
}

void Snek::clean() {}

void TestComponent::Init()
{
	GAME.RegisterEventHandler<TestEventHandler>(EventHandlerPriority::TEST);
	SoundManager& sm = SoundManager::getInstance();
	sm.LoadMusic("../assets/sound/The Builder.mp3");
	sm.SetMusicVolume(0.01f);
	sm.PlayMusic(LOOP_SOUND_FOREVER, 500);
	AddObject("player", make_unique<Snek>());
}

void TestEventHandler::Handle(SDL_Event const& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		KeyEvent(SDL_GetKeyboardState(nullptr));
		break;
	}
}

void TestEventHandler::KeyEvent(Uint8 const* state)
{
	Snek& player = GAME.GetComponent<TestComponent>("test").GetObject<Snek>("player");
	Random rnd;
	Uint8 right = state[SDL_SCANCODE_RIGHT];
	Uint8 left = state[SDL_SCANCODE_LEFT];
	Uint8 down = state[SDL_SCANCODE_DOWN];
	Uint8 up = state[SDL_SCANCODE_UP];
	Uint8 mode = state[SDL_SCANCODE_TAB];
	if (mode) player.mode = (player.mode + 1) % 3;
	if (player.mode == 0) {
		player.setTexture(player.t);
		if (!right && !left && !down && !up) {
			player.setMoving(false);
			player.mod = Color(255, 255, 255);
			return;
		}
		int x = 0, y = 0;
		if (right) x += 1;
		if (left) x -= 1;
		if (down) y += 1;
		if (up) y -= 1;
		player.face(Direction(static_cast<float>(x), static_cast<float>(y)));
		player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
		player.setVelocity(player.getFacingDirection() * player.v);
		player.setMoving(true);
	}
	else if (player.mode == 1) {
		player.setTexture(player.t120l);
		if (right || left) {
			player.face(Direction(right ? 1.f : left ? -1.f : 0, 0));
			player.setVelocity(Velocity(player.v.x * player.getFacingDirection().x, player.getVelocity().y));
			player.setMoving(true);
		}
		else player.setMoving(false);
		if (up && !player.isAirborne()) {
			player.setAirborne(true);
			player.setGravity(Velocity(0, 1));
			player.setVelocity(Velocity(player.getVelocity().x, -player.v.y));
		}
	}
	else if (player.mode == 2) {
		player.setTexture(player.t120r);
		if (right) player.angle = (player.angle + 5) % 360;
		if (left) player.angle = (player.angle - 5) % 360;
		float rads = player.angle / 180 * static_cast<float>(M_PI);
		float x = cos(rads);
		float y = sin(rads);
		player.face(Direction(x, y));
		if (up || down) {
			player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
			player.setVelocity(Velocity(x, y) * player.v * (up ? 1.f : down ? -1.f : 0));
			player.setMoving(true);
		}
		else player.setMoving(false);
	}
}
