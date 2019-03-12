#include "EventHandler.hpp"

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
