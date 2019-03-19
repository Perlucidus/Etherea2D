#pragma once

#include "CustomEventData.hpp"
#include <SDL_events.h>

BETTER_ENUM(EventHandlerPriority, uint32_t, WINDOW, SPLASH, TEST)

class EventHandler {
public:
	EventHandler() = default;
	virtual ~EventHandler() = default;
	EventHandler(EventHandler const&) = delete;
	void operator=(EventHandler const&) = delete;
public:
	void Handle(SDL_Event const&);
private:
	virtual bool handle(SDL_Event const&) = 0;
public:
	template<typename CustomEventDataT, typename... TArgs>
	static void PushCustomEvent(CustomEvent code, TArgs... args);
private:
	static void PushCustomEvent(CustomEvent code, void* data1 = nullptr, void* data2 = nullptr);
};

template<typename CustomEventDataT, typename ...TArgs>
inline void EventHandler::PushCustomEvent(CustomEvent code, TArgs ...args)
{
	PushCustomEvent(code, new CustomEventDataT(args...));
}
