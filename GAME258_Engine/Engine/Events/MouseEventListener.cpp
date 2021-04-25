#include "MouseEventListener.h"
#include "../Core/Engine.h"

Engine* MouseEventListener::engineInstance = nullptr;
ivec2 MouseEventListener::mouse = ivec2();
ivec2 MouseEventListener::prevMouse = ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener() {
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(Engine* engine_) {
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event event_) {
	if (event_.type == SDL_MOUSEBUTTONDOWN) {
		UpdateMousePosition();
		NotifyMousePressed(event_.button.button);
	}
	else if (event_.type == SDL_MOUSEBUTTONUP) {
		UpdateMousePosition();
		NotifyMouseReleased(event_.button.button);
	}
	else if (event_.type == SDL_MOUSEMOTION) {
		UpdateMousePosition();
		NotifyMouseMove();
	}
	else if (event_.type == SDL_MOUSEWHEEL) {
		NotifyMouseScroll(event_.wheel.y);
	}
}

void MouseEventListener::NotifyMousePressed(int buttonType_) {
	if (engineInstance) engineInstance->NotifyMousePressed(mouse, buttonType_);
}

void MouseEventListener::NotifyMouseReleased(int buttonType_) {
	if (engineInstance) engineInstance->NotifyMouseReleased(mouse, buttonType_);
}

void MouseEventListener::NotifyMouseMove() {
	if (engineInstance) engineInstance->NotifyMouseMove(mouse);
}

void MouseEventListener::NotifyMouseScroll(int y_) {
	if (engineInstance) engineInstance->NotifyMouseScroll(y_);
}

void MouseEventListener::UpdateMousePosition() {
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = static_cast<int>(engineInstance->GetScreenHeight()) - tmpY;

	if (firstUpdate) {
		prevMouse.x = mouse.x = tmpX;
		prevMouse.y = mouse.y = tmpY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpX;
		mouse.y = tmpY;
	}
}
