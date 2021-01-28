#include "Game1.h"

//always declare the constructor of parent class when inheriting
Game1::Game1() : GameManager(), currentSceneNum(0), currentScene(nullptr) {
}

Game1::~Game1() {
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate() {
	//initialize our engine, set the start scene and set the curr num to 0, then return OnCreate to create our scene
	if (Engine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	} 
	cout << "Engine's scene not initalized to 0" << endl;
	return false;
}

void Game1::Update(const float deltaTime_) {
	//if our current scene num is not equal to the engine's current scene, build the scene
	if (currentSceneNum != Engine::GetInstance()->GetCurrentScene()) BuildScene();
	
	//otherwise, update the scene as needed
	currentScene->Update(deltaTime_);
}

//render our scene
void Game1::Render() {
	currentScene->Render();
}

/*leaving one scene and moving into another scene
1. delete all previous scnees obj and dealocate memory properly
2. create switch statement
case 1: change to new game scene, if scene number is not 0 (the default scene)
default case: change to start scene AKA default scene
3. change currentSceneNum to the current scene
4. if OnCreate fails, print console msg and the Exit program*/
void Game1::BuildScene() {
	delete currentScene;
	currentScene = nullptr;

	switch (Engine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = Engine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		cout << "Scene failed to create." << endl;
		Engine::GetInstance()->Exit();
	}
}
