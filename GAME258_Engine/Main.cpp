#include "Engine/Core/Engine.h"
#include "Game/Game1.h"

int main(int argc, char* argv[]) {
	//set the game manager to a new instance of game1 class
	Engine::GetInstance()->SetGameManager(new Game1);

	//if OnCreate did not run delete our engine and break // OnCreate is setting the NAME, WIDTH, HEIGHT variables
	if (!Engine::GetInstance()->OnCreate("Game258 Engine", 800, 600)) {
		cout << "Failed to initialize engine" << endl;
		return 0;
	}
	
	/*if OnCreate works
	call our engine's run function.
	when run is finished, exit the program.*/
	Engine::GetInstance()->Run();
	return 0;
}