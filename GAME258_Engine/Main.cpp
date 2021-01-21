#include "Engine/Core/Engine.h"

Engine* engine;

int main(int argc, char* argv[]) {
	//init window
	engine = new Engine();
	
	//if OnCreate did not run delete our engine and break // OnCreate is setting the NAME, WIDTH, HEIGHT variables
	if (!engine->OnCreate("GAME258 Engine", 800, 600)) {
		delete engine;
		engine = nullptr;
		return 0;
	}
	
	/* Call engine Run function to begin game loop
		1. delete engine and set to nullptr
		2. return 0 to close out our project
	*/
	engine->Run();
	delete engine;
	engine = nullptr;
	return 0;
}