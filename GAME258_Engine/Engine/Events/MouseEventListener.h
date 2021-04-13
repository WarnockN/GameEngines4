#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class Engine;

using namespace glm;

class MouseEventListener {
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();

	static void RegisterEngineObject(Engine* engine_);
	static void Update(SDL_Event event_);

	static void NotifyMousePressed(int buttonType_);
	static void NotifyMouseReleased(int buttonType_);
	static void NotifyMouseMove();
	static void NotifyMouseScroll(int y_);

	inline static vec2 GetPreviousMousePosition() { return prevMouse; }
	inline static vec2 GetMousePosition() { return mouse; }
	inline static vec2 GetMouseOffset() { return ivec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y); }

private:
	static Engine* engineInstance;
	static ivec2 mouse, prevMouse;
	static bool firstUpdate;
	static void UpdateMousePosition();
};
#endif

