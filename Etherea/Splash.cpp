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
	txtr.AlphaMod(static_cast<Uint8>((progress < 0.7 ? progress : (1 - progress)) * 255 / 0.7f));
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
