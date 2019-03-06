#include "Timer.hpp"

Timer::Timer(Uint32 delay, TimerCallback callback) : delay(delay)
{
	data.callback = callback;
	data.param = nullptr;
}

Timer::~Timer()
{
	if (id) SDL_RemoveTimer(id);
}

Uint32 Timer::getDelay() const
{
	return delay;
}

void Timer::setCallback(TimerCallback func)
{
	data.callback = func;
}

void Timer::start(void* param)
{
	if (!data.callback)
		throw TimerException("Callback unset");
	data.param = param;
	id = SDL_AddTimer(delay, &Timer::tick, &data);
}

void Timer::abort()
{
	if (!id)
		throw TimerException("Timer is not running");
	if (!SDL_RemoveTimer(id))
		throw TimerException();
	id = 0;
}

Uint32 SDLCALL Timer::tick(Uint32 interval, void* param)
{
	TimerCallbackData* data = static_cast<TimerCallbackData*>(param);
	TimerResult res = data->callback(interval, data->param);
	switch (res) {
	case TimerResult::ABORT:
		return 0;
	case TimerResult::CONTINUE:
		return interval;
	case TimerResult::RESET:
		return SDL_MAX_UINT32;
	}
	return 0;
}
