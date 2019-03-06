#pragma once

#include "Common.hpp"
#include <functional>

enum class TimerResult
{
	ABORT,
	CONTINUE,
	RESET
};

using TimerCallback = std::function<TimerResult(Uint32 interval, void* param)>;

class Timer {
public:
	Timer(Uint32 delay, TimerCallback callback = nullptr);
	virtual ~Timer();

	Uint32 getDelay() const;

	void setCallback(TimerCallback callback);
	void start(void* param);
	void abort();
private:
	struct TimerCallbackData { TimerCallback callback; void* param; } callback;
	static Uint32 SDLCALL tick(Uint32 interval, void* data);
private:
	SDL_TimerID id;
	TimerCallbackData data;
	Uint32 delay;
};
