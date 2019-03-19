#include "Splash.hpp"
#include "Log.hpp"

#define RENDER GetComponent<RenderComponent>()

Splash::Splash() : Entity("splash")
{
	Texture texture = GAME.GetRenderer().LoadTexture("../assets/textures/splash.png");
	AddComponent<RenderComponent>(texture);
}

void Splash::render(Renderer & renderer)
{
	renderer.CopyTo(RENDER.getTexture(), Rectangle(Position(0), RENDER.getTextureSize()));
}

void Splash::update()
{
	const float ratio = 0.67f;
	SDL_Color color = RENDER.getTexture().GetColorMod();
	color.a = static_cast<Uint8>((progress < ratio ? (progress / ratio) : ((1 - progress) / (1 - ratio))) * 255);
	RENDER.getTexture().ColorMod(color);
}

void Splash::setProgress(float p)
{
	progress = p;
}

SplashScreen::SplashScreen() : timer(2000, &SplashScreen::end) {}

void SplashScreen::initialize()
{
	GAME.RegisterEventHandler<SplashEventHandler>(EventHandlerPriority::SPLASH);
	timer.start(nullptr);
	start = SDL_GetTicks();
}

void SplashScreen::update()
{
	if (timer.isRunning()) {
		splash.setProgress(static_cast<float>(SDL_GetTicks() - start) / timer.getDelay());
		splash.update();
	}
}

void SplashScreen::render(Renderer & renderer)
{
	if (timer.isRunning())
		splash.render(renderer);
}

TimerResult SplashScreen::end(Uint32 interval, void* param)
{
	STDLOG << "Splash ended with interval " << interval;
	EventHandler::PushCustomEvent<SplashEventData>(CustomEvent::SPLASH);
	return TimerResult::ABORT;
}

bool SplashEventHandler::handle(SDL_Event const& event)
{
	if (event.type != SDL_USEREVENT || event.user.code != CustomEvent::SPLASH)
		return false;
	GAME.EraseComponent("splash");
	/////////////////////////////////////////////////
	GAME.GetComponent<GameComponent>("test").initialize();
	/////////////////////////////////////////////////
	return true;
}
