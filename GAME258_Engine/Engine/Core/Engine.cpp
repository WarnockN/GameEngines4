#include "Engine.h"

Engine::Engine() : window(nullptr), isRunning(false) {}

Engine::~Engine() {

}

bool Engine::OnCreate(string name_, int width_, int height_) {
	window = new Window();

	//if OnCreate didnt run, print console msg, and pack up and go home
	if (!window->OnCreate(name_, width_, height_)) {
		cout << "Failed to initialize" << endl;
		OnDestroy();
		return isRunning = false;
	}
	//if OnCreate works, set isRunning to true
	return isRunning = true;
}

void Engine::Run() {
	//while isRunning is true, continuously call Update/Render
	while (isRunning) {
		//update -- this number is 1/60 AKA 60FPS
		Update(0.016f);
		Render();
	}
	
	//when isRunning is false, pack up and go home
	OnDestroy();
}

void Engine::Update(const float deltaTime_) {

}

/*Render the window
	1. set color to black
	2. clear the buffer bit and depth bit
	//RENDER EVERYTHING FOR THE GAME//
	3. call the game render
*/
void Engine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//Call game render
	SDL_GL_SwapWindow(window->GetWindow());
}

/*clean up our stuffs
	1. delete window / nullptr
	2. call SDL_Quit - close out entire proj
	3. call exit(0) to finalize exit. Exit the entire program
*/
void Engine::OnDestroy() {
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
