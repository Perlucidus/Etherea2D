#include "EventHandler.hpp"
#include "Common.hpp"

void EventHandler::Handle(SDL_Event const& event)
{
	if (handle(event) && event.type == SDL_USEREVENT)
		delete static_cast<CustomEventData*>(event.user.data1);
}

void EventHandler::PushCustomEvent(CustomEvent code, void* data1, void* data2)
{
	SDL_Event evt;
	SDL_UserEvent userevt;
	SDL_zero(evt);
	SDL_zero(userevt);
	userevt.code = code;
	userevt.data1 = data1;
	userevt.data2 = data2;
	evt.type = userevt.type = SDL_USEREVENT;
	evt.user = userevt;
	SDL_PushEvent(&evt);
}
