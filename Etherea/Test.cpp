#include "Test.hpp"

Snek::Snek() : Entity("snake"), render(Texture()), animation(Size(4, 1), Size(134, 134)), face(Direction(1, 0)),
location(Point(0, 0)), movement(Velocity(0)), gravity(10), v(Velocity(100, 100)), s(0.1f), mode(0), mod(Color(255, 255, 255))
{
	t = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png");
	t120l = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120l.png");
	t120r = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120r.png");
	render.setTexture(t);
	render.setRotationCenter(Point(40, 40));
	render.setFlip(SDL_FLIP_HORIZONTAL);
	face.face(Direction(1, 0));
}

void Snek::draw(Renderer & renderer)
{
	if (!render.isEnabled())
		return;
	Rectangle src = animation.getFrameRectangle(), dst(location.getLocation(), animation.getFrameSize());
	Uint32 f = render.getFlip();
	Direction facing = face.getFacingDirection();
	if (facing.x < 0) f ^= SDL_FLIP_HORIZONTAL;
	if (facing.y < 0) f ^= SDL_FLIP_VERTICAL;
	double rads;
	if (facing.x == 0)
		rads = facing.y * M_PI / 2;
	else
		rads = atan(static_cast<double>(facing.y) / facing.x);
	double angle = rads / M_PI * 180.;
	render.getTexture().ColorMod(mod);
	renderer.CopyEx(render.getTexture(), src, dst, angle, render.getRotationCenter(), static_cast<SDL_RendererFlip>(f));
}

void Snek::update()
{
	bool animate = animation.canAnimate();
	if (movement.isEnabled()) {
		location.setLocation(location.getLocation() + Point(movement.getMovementDistance()));
		if (animate)
			animation.cycleColumn();
	}
	else animation.setCurrentFrame(Size(3, 0)); //Standing
	movement.updateMovementTimer();
	if (animate)
		animation.updateAnimationTimer();
}

void Snek::clean() {}

void Snek::setVelocity(Velocity velocity)
{
	movement.setVelocity(velocity);
	animation.setAnimationSpeed(s * std::abs(velocity.x));
}

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
		player.render.setTexture(player.t);
		if (!right && !left && !down && !up) {
			player.movement.disable();
			player.mod = Color(255, 255, 255);
			return;
		}
		int x = 0, y = 0;
		if (right) x += 1;
		if (left) x -= 1;
		if (down) y += 1;
		if (up) y -= 1;
		if (!x && !y)
			player.face.face(Direction(1, 0));
		else
			player.face.face(Direction(static_cast<float>(x), static_cast<float>(y)));
		player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
		player.setVelocity(player.face.getFacingDirection() * player.v);
		player.movement.enable();
	}
	else if (player.mode == 1) {
		player.render.setTexture(player.t120l);
		if (right || left) {
			player.face.face(Direction(right ? 1.f : left ? -1.f : 0, 0));
			player.setVelocity(Velocity(player.v.x * player.face.getFacingDirection().x, player.movement.getVelocity().y));
			player.movement.enable();
		}
		else player.movement.disable();
		/*if (up && !player.isAirborne()) {
			player.setAirborne(true);
			player.setGravity(Velocity(0, 1));
			player.setVelocity(Velocity(player.getVelocity().x, -player.v.y));
		}*/
	}
	else if (player.mode == 2) {
		player.render.setTexture(player.t120r);
		if (right) player.render.setRenderAngle((static_cast<int>(player.render.getRenderAngle()) + 5) % 360);
		if (left) player.render.setRenderAngle((static_cast<int>(player.render.getRenderAngle()) - 5) % 360);
		float rads = static_cast<float>(player.render.getRenderAngle()) / 180 * static_cast<float>(M_PI);
		float x = cos(rads);
		float y = sin(rads);
		if (!x && !y)
			player.face.face(Direction(1, 0));
		else
			player.face.face(Direction(x, y));
		if (up || down) {
			player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
			player.setVelocity(Velocity(x, y) * player.v * (up ? 1.f : down ? -1.f : 0));
			player.movement.enable();
		}
		else player.movement.disable();
	}
}
