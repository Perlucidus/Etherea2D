#include "Test.hpp"

Snek::Snek(Texture const & texture) : Entity("snake", texture, Position(), Size(134, 134), Size(4, 1),
	10, SDL_FLIP_HORIZONTAL, Velocity(10, 10)), mod(Color(255, 255, 255))
{
	facing = Direction(1, 0);
}

void Snek::changeColor(SDL_Color color)
{
	mod = color;
}

void Snek::draw(Renderer & renderer)
{
	texture.ColorMod(mod);
	Entity::draw(renderer);
}

void Snek::update()
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

void Snek::clean() {}

TestComponent::TestComponent()
{
	GAME.RegisterEventHandler<TestEventHandler>(EventHandlerPriority::TEST);
	SoundManager& sm = SoundManager::getInstance();
	sm.LoadMusic("../assets/sound/The Builder.mp3");
	sm.SetMusicVolume(0.01f);
	sm.PlayMusic(LOOP_SOUND_FOREVER, 500);
	AddObject("player", make_unique<Snek>(GAME.GetRenderer().LoadTexture("../assets/textures/char2-alpha.png")));
	GetObject<Snek>("player").hide();
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

void TestEventHandler::KeyEvent(Uint8 const * state)
{
	Snek& player = GAME.GetComponent<TestComponent>("test").GetObject<Snek>("player");
	Random rnd;
	Uint8 right = state[SDL_SCANCODE_RIGHT];
	Uint8 left = state[SDL_SCANCODE_LEFT];
	Uint8 down = state[SDL_SCANCODE_DOWN];
	Uint8 up = state[SDL_SCANCODE_UP];
	if (!right && !left && !down && !up) {
		player.setMoving(false);
		player.changeColor(Color(255, 255, 255));
		return;
	}
	int x = 0, y = 0;
	if (right) x += 1;
	if (left) x -= 1;
	if (down) y += 1;
	if (up) y -= 1;
	player.setFacingDirection(Direction(static_cast<float>(x), static_cast<float>(y)));
	player.changeColor(Color(rnd.next(255), rnd.next(255), rnd.next(255)));
	player.setMoving(true);
}

void TestEventHandler::KeyDown(SDL_KeyboardEvent const & event)
{
	Snek& player = GAME.GetComponent<TestComponent>("test").GetObject<Snek>("player");
	//Random rnd;
	switch (event.keysym.sym) {
	case SDLK_RIGHT:
	case SDLK_LEFT:
	case SDLK_DOWN:
	case SDLK_UP:
		player.setFacingDirection(GetKeyDirection(event.keysym.sym, player));
		player.setMoving(true);
		break;
		/*case SDLK_UP:
			player.changeColor(Color(rnd.next(256), rnd.next(256), rnd.next(256)));
			break;
		case SDLK_DOWN:
			player.changeColor(Color(255, 255, 255));
			break;*/
	}
}

void TestEventHandler::KeyUp(SDL_KeyboardEvent const & event)
{
	Snek& player = GAME.GetComponent<TestComponent>("test").GetObject<Snek>("player");
	Direction key = GetKeyDirection(event.keysym.sym, player);
	Direction face = player.getFacingDirection();
	switch (event.keysym.sym) {
	case SDLK_RIGHT:
	case SDLK_LEFT:
	case SDLK_DOWN:
	case SDLK_UP:
		if (face.getX() == key.getX())
			player.setFacingDirection(player.getFacingDirection() * Direction(0, 1));
		if (face.getY() == key.getY())
			player.setFacingDirection(player.getFacingDirection() * Direction(1, 0));
		break;
	}
	if (player.getFacingDirection() == 0) {
		player.setMoving(false);
		player.setFacingDirection(face);
	}
}

Direction TestEventHandler::GetKeyDirection(SDL_Keycode key, Snek & player)
{
	Direction face = player.getFacingDirection();
	float x = face.getX(), y = face.getY();
	if (!player.isMoving())
		y = x = 0;
	switch (key) {
	case SDLK_RIGHT:
		x = 1;
		break;
	case SDLK_LEFT:
		x = -1;
		break;
	case SDLK_DOWN:
		y = 1;
		break;
	case SDLK_UP:
		y = -1;
		break;
	}
	return Direction(x, y);
}
