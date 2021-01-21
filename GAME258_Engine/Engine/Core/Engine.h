#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

using namespace std;

class Engine {
public:
	Engine();
	~Engine();
	bool OnCreate(string name_, int width_, int height_);
	void Run();

	//getters
	inline bool GetIsRunning() { return isRunning; }

private:
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;
};
#endif
