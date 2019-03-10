#include "Splash.hpp"
#include "SDLStruct.hpp"
////////////////////////////
#include "Test.hpp"
////////////////////////////

Splash::Splash(Texture const& texture, Uint32 delay) : Renderable("splash", texture, Position(0)), timer(delay)
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
	renderer.CopyTo(texture, Rect(pos, size));
}

void Splash::update() {}

void Splash::clean() {}

TimerResult Splash::end(Uint32 interval, void* param)
{
	STDLOG << "Splash ended with interval " << interval;
	SDL_Event evt;
	SDL_UserEvent userevt;
	userevt.code = 0;
	userevt.data2 = userevt.data1 = nullptr;
	evt.type = userevt.type = SDL_USEREVENT;
	evt.user = userevt;
	SDL_PushEvent(&evt);
	return TimerResult::ABORT;
}

SplashScreen::SplashScreen()
{
	GAME.RegisterEventHandler<SplashEventHandler>(EventHandlerPriority::SPLASH);
	AddObject("splash", make_unique<Splash>(GAME.GetRenderer().LoadTexture("../assets/textures/splash.png"), 2000));
}

void SplashEventHandler::Handle(SDL_Event const& event)
{
	if (event.type != SDL_USEREVENT || event.user.code != CustomEvent::SPLASH)
		return;
	GAME.EraseComponent("splash");
	GAME.GetComponent<TestComponent>("test").GetObject<Snek>("player").show();
}
