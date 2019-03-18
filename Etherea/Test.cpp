#include "Test.hpp"
#include "Random.hpp"
#include "RenderComponent.hpp"
#include "AnimationComponent.hpp"
#include "FaceComponent.hpp"
#include "GravityComponent.hpp"
#include "LocationComponent.hpp"
#include "PhysicsComponent.h"
#include "MovementComponent.hpp"

#define RENDER GetComponent<RenderComponent>()
#define ANIMATION GetComponent<AnimationComponent>()
#define FACE GetComponent<FaceComponent>()
#define LOCATION GetComponent<LocationComponent>()
#define PHYSICS GetComponent<PhysicsComponent>()
#define MOVEMENT GetComponent<MovementComponent>()
#define GRAVITY GetComponent<GravityComponent>()

Snek::Snek() : Entity("snake"), v(Velocity(10, 10)), s(0.1f), mode(0), mod(Color(255, 255, 255))
{
	AddComponent<RenderComponent>(Texture());
	AddComponent<AnimationComponent>(Size(4, 1), Size(134, 134));
	AddComponent<FaceComponent>(Direction(1, 0));
	AddComponent<LocationComponent>(Point(0, 0));
	AddComponent<PhysicsComponent>(Size(80, 40));
	AddComponent<MovementComponent>(Velocity(0));
	AddComponent<GravityComponent>(10.f);
	t = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png");
	t120l = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120l.png");
	t120r = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120r.png");
	RENDER.setTexture(t);
	RENDER.setRotationCenter(Point(40, 20));
	RENDER.setFlip(SDL_FLIP_HORIZONTAL);
	FACE.face(Direction(1, 0));
}

void Snek::draw(Renderer & renderer)
{
	if (!RENDER.isEnabled())
		return;
	Rectangle src = ANIMATION.getFrameRectangle(), dst(LOCATION.getLocation(), ANIMATION.getFrameSize());
	Uint32 f = RENDER.getFlip();
	Direction facing = FACE.getFacingDirection();
	if (facing.x < 0) f ^= SDL_FLIP_HORIZONTAL;
	if (facing.y < 0) f ^= SDL_FLIP_VERTICAL;
	double rads;
	if (facing.x == 0)
		rads = facing.y * M_PI / 2;
	else
		rads = atan(static_cast<double>(facing.y) / facing.x);
	double angle = rads / M_PI * 180.;
	RENDER.getTexture().ColorMod(mod);
	renderer.CopyEx(RENDER.getTexture(), src, dst, angle, RENDER.getRotationCenter(), static_cast<SDL_RendererFlip>(f));
}

void Snek::update()
{
	bool animate = ANIMATION.canAnimate();
	if (MOVEMENT.isEnabled()) {
		LOCATION.setLocation(LOCATION.getLocation() + Point(MOVEMENT.getMovementDistance()));
		if (animate)
			ANIMATION.cycleColumn();
	}
	else ANIMATION.setCurrentFrame(Size(3, 0)); //Standing
	MOVEMENT.updateMovementTimer();
	if (animate)
		ANIMATION.updateAnimationTimer();
}

void Snek::clean() {}

void Snek::setVelocity(Velocity velocity)
{
	velocity = Velocity(std::fminf(velocity.x, 105), std::fminf(velocity.y, 105));
	MOVEMENT.setVelocity(velocity * 12);
	ANIMATION.setAnimationSpeed(s * std::abs(velocity.x) * 12);
}

void TestWorld::initialize()
{
	GAME.RegisterEventHandler<TestEventHandler>(EventHandlerPriority::TEST);
	SoundManager& sm = SoundManager::getInstance();
	sm.LoadMusic("../assets/sound/The Builder.mp3");
	sm.SetMusicVolume(0.01f);
	sm.PlayMusic(LOOP_SOUND_FOREVER, 500);
	AddEntity<Snek>();
	AddEntity<Plant>("plant");
}

void TestWorld::update()
{
	World::update();
}

bool TestEventHandler::handle(SDL_Event const& event)
{
	switch (event.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		KeyEvent(SDL_GetKeyboardState(nullptr));
		return true;
	case SDL_USEREVENT:
		if (event.user.code != CustomEvent::ENTITY_COLLISION)
			return false;
		EntityCollisionEventData& data = *static_cast<EntityCollisionEventData*>(event.user.data1);
		if (data.getId1() == "plant" || data.getId2() == "plant") {
			Plant& plant = GAME.GetComponent<TestWorld>("test").GetEntity<Plant>("plant");
			plant.GetComponent<RenderComponent>().setTexture(Random().next() % 2 ? plant.t120l : plant.t120r);
		}
		return true;
	}
	return false;
}

void TestEventHandler::KeyEvent(Uint8 const* state)
{
	Snek& player = GAME.GetComponent<TestWorld>("test").GetEntity<Snek>("snake");
	Random rnd;
	Uint8 right = state[SDL_SCANCODE_RIGHT];
	Uint8 left = state[SDL_SCANCODE_LEFT];
	Uint8 down = state[SDL_SCANCODE_DOWN];
	Uint8 up = state[SDL_SCANCODE_UP];
	Uint8 mode = state[SDL_SCANCODE_TAB];
	if (mode) player.mode = (player.mode + 1) % 3;
	if (player.mode == 0) {
		player.RENDER.setTexture(player.t);
		if (!right && !left && !down && !up) {
			player.MOVEMENT.disable();
			player.mod = Color(255, 255, 255);
			return;
		}
		int x = 0, y = 0;
		if (right) x += 1;
		if (left) x -= 1;
		if (down) y += 1;
		if (up) y -= 1;
		if (!x && !y) {
			player.MOVEMENT.disable();
			return;
		}
		player.FACE.face(Direction(static_cast<float>(x), static_cast<float>(y)));
		player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
		player.setVelocity(player.FACE.getFacingDirection() * player.v);
		player.MOVEMENT.enable();
	}
	else if (player.mode == 1) {
		player.RENDER.setTexture(player.t120l);
		if (right || left) {
			player.FACE.face(Direction(right ? 1.f : left ? -1.f : 0, 0));
			player.setVelocity(Velocity(player.v.x * player.FACE.getFacingDirection().x, player.MOVEMENT.getVelocity().y));
			player.MOVEMENT.enable();
		}
		else player.MOVEMENT.disable();
		/*if (up && !player.isAirborne()) {
			player.setAirborne(true);
			player.setGravity(Velocity(0, 1));
			player.setVelocity(Velocity(player.getVelocity().x, -player.v.y));
		}*/
	}
	else if (player.mode == 2) {
		player.RENDER.setTexture(player.t120r);
		if (right) player.RENDER.setRenderAngle((static_cast<int>(player.RENDER.getRenderAngle()) + 5) % 360);
		if (left) player.RENDER.setRenderAngle((static_cast<int>(player.RENDER.getRenderAngle()) - 5) % 360);
		float rads = static_cast<float>(player.RENDER.getRenderAngle()) / 180 * static_cast<float>(M_PI);
		float x = cos(rads);
		float y = sin(rads);
		if (!x && !y)
			player.FACE.face(Direction(1, 0));
		else
			player.FACE.face(Direction(x, y));
		if (up || down) {
			player.mod = Color(rnd.next(255), rnd.next(255), rnd.next(255));
			player.setVelocity(Velocity(x, y) * player.v * (up ? 1.f : down ? -1.f : 0));
			player.MOVEMENT.enable();
		}
		else player.MOVEMENT.disable();
	}
}

Plant::Plant(string const& id) : Entity(id)
{
	AddComponent<RenderComponent>(Texture());
	AddComponent<AnimationComponent>(Size(4, 3), Size(134, 134), 0.f, Size(2, 2));
	AddComponent<FaceComponent>(Direction(1, 0));
	AddComponent<LocationComponent>(Point(600, 300));
	AddComponent<PhysicsComponent>(Size(80, 70));
	t = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png");
	t120l = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120l.png");
	t120r = GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha120r.png");
	RENDER.setTexture(t);
	RENDER.setFlip(SDL_FLIP_HORIZONTAL);
	FACE.face(Direction(1, 0));
}

void Plant::draw(Renderer& renderer)
{
	if (!RENDER.isEnabled())
		return;
	Rectangle src = ANIMATION.getFrameRectangle(), dst(LOCATION.getLocation(), ANIMATION.getFrameSize());
	Uint32 f = RENDER.getFlip();
	Direction facing = FACE.getFacingDirection();
	if (facing.x < 0) f ^= SDL_FLIP_HORIZONTAL;
	if (facing.y < 0) f ^= SDL_FLIP_VERTICAL;
	Random rnd;
	if (RENDER.getTexture() == t120l || RENDER.getTexture() == t120r)
		RENDER.getTexture().ColorMod(Color(rnd.next(), rnd.next(), rnd.next()));
	renderer.CopyEx(RENDER.getTexture(), src, dst, 0, static_cast<SDL_RendererFlip>(f));
}

void Plant::update()
{
	if (ANIMATION.canAnimate()) {
		ANIMATION.cycleColumn();
		ANIMATION.updateAnimationTimer();
	}
}

void Plant::clean() {}
