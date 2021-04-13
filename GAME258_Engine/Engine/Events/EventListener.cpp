#include "EventListener.h"
#include "../Core/Engine.h"

EventListener::~EventListener() {

}

void EventListener::Update() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) Engine::GetInstance()->Exit();

		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
			break;
		
		case SDL_MOUSEBUTTONUP:
			break;
		
		case SDL_MOUSEMOTION:
			break;
		
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(sdlEvent);
			break;
		
		default:
			break;
		}
	}
}
