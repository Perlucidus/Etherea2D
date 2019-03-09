#include "Splash.hpp"
#include "TextureManager.hpp"

Splash::Splash(string const& id, Uint32 delay) : Renderable(id, Position(0)), timer(delay)
{
	timer.setCallback(&Splash::end);
	timer.start(nullptr);
	start = SDL_GetTicks();
}

void Splash::draw(Renderer & renderer)
{
	TextureManager& tm = TextureManager::getInstance(renderer);
	Texture& txtr = tm.GetTexture(id);
	Size size;
	txtr.Query(size);
	float progress = static_cast<float>(SDL_GetTicks() - start) / timer.getDelay();
	const float ratio = 0.67f;
	SDL_Color color = txtr.GetColorMod();
	color.a = static_cast<Uint8>((progress < ratio ? (progress / ratio) : ((1 - progress) / (1 - ratio))) * 255);
	txtr.ColorMod(color);
	tm.Draw(id, pos, size);
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
