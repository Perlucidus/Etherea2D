#include "Splash.hpp"

Splash::Splash(Texture const& texture, Uint32 delay) : Renderable("splash", texture), timer(delay)
{
	timer.setCallback(&Splash::end);
	timer.start(nullptr);
	start = SDL_GetTicks();
}

void Splash::draw(Renderer & renderer)
{
	Size size;
	texture.Query(size);
	float progress = static_cast<float>(SDL_GetTicks() - start) / timer.getDelay();
	const float ratio = 0.67f;
	SDL_Color color = texture.GetColorMod();
	color.a = static_cast<Uint8>((progress < ratio ? (progress / ratio) : ((1 - progress) / (1 - ratio))) * 255);
	texture.ColorMod(color);
	renderer.CopyTo(texture, Rectangle(Position(0), size));
}

void Splash::update() {}

void Splash::clean() {}

TimerResult Splash::end(Uint32 interval, void* param)
{
	STDLOG << "Splash ended with interval " << interval;
	EventHandler::PushCustomEvent(CustomEvent::SPLASH);
	return TimerResult::ABORT;
}

void SplashScreen::Init()
{
	GAME.RegisterEventHandler<SplashEventHandler>(EventHandlerPriority::SPLASH);
	AddObject("splash", make_unique<Splash>(GAME.GetRenderer().LoadTexture("../assets/textures/splash.png"), 2000));
}

void SplashEventHandler::Handle(SDL_Event const& event)
{
	if (event.type != SDL_USEREVENT || event.user.code != CustomEvent::SPLASH)
		return;
	GAME.EraseComponent("splash");
	/////////////////////////////////////////////////
	GAME.GetComponent<GameComponent>("test").Init();
	/////////////////////////////////////////////////
}
