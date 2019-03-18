#include "Timer.hpp"

Timer::Timer(Uint32 delay, TimerCallback callback) : delay(delay), callback(callback), param(nullptr) {}

Timer::~Timer()
{
	if (id) SDL_RemoveTimer(id);
}

Uint32 Timer::getDelay() const
{
	return delay;
}

bool Timer::isRunning() const
{
	return id;
}

void Timer::setCallback(TimerCallback func)
{
	callback = func;
}

void Timer::start(void* param)
{
	if (id)
		throw TimerException("Timer already running");
	if (!callback)
		throw TimerException("Callback unset");
	param = param;
	id = SDL_AddTimer(delay, &Timer::tick, this);
}

void Timer::abort()
{
	if (!id)
		throw TimerException("Timer is not running");
	id = 0;
	if (!SDL_RemoveTimer(id))
		throw TimerException();
}

Uint32 SDLCALL Timer::tick(Uint32 interval, void* param)
{
	Timer* timer = static_cast<Timer*>(param);
	TimerResult res = timer->callback(interval, timer->param);
	switch (res) {
	case TimerResult::CONTINUE:
		return interval;
	case TimerResult::RESET:
		return SDL_MAX_UINT32;
	case TimerResult::ABORT:
	default:
		timer->id = 0;
		return 0;
	}
}
