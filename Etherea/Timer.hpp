#pragma once

#include "Common.hpp"
#include "Exception.hpp"
#include <functional>
#include <SDL_timer.h>

enum class TimerResult
{
	CONTINUE,
	RESET,
	ABORT
};

using TimerCallback = std::function<TimerResult(Uint32 interval, void* param)>;

class Timer {
public:
	Timer(Timer const& other) = delete;

	Timer(Uint32 delay, TimerCallback callback = nullptr);
	virtual ~Timer();

	Uint32 getDelay() const;
	bool isRunning() const;

	void setCallback(TimerCallback callback);
	void start(void* param);
	void abort();
private:
	static Uint32 SDLCALL tick(Uint32 interval, void* data);
private:
	SDL_TimerID id;
	TimerCallback callback;
	void* param;
	Uint32 delay;
};

class TimerException : public SDLException {
public:
	TimerException();
	TimerException(char const* reason);

	char const* what() const noexcept override;
private:
	char const* reason;
};
