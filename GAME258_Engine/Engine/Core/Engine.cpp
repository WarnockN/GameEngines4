#include "Engine.h"

//SHAKED SAYS: always make sure to redeclare any static variables at the top of the class!
unique_ptr<Engine> Engine::engineInstance = nullptr;

Engine::Engine() : window(nullptr), isRunning(false), fps(60), gameManager(nullptr), currentSceneNum(0) {}

Engine::~Engine() {}

//get our engine instance -- use this to access anything in the engine class that is public.
Engine* Engine::GetInstance() {
	//if our engine instance returns nullptr, restart the engine.
	//if everything works, simply get the engineInstance
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new Engine);
	}

	return engineInstance.get();
}

bool Engine::OnCreate(string name_, int width_, int height_) {
	Debug::OnCreate();
	window = new Window();

	//if OnCreate didnt run, print console msg, and pack up and go home
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize window.", "Engine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	
	//if game exists -- if the game does exist, if OnCreate didnt run, print console msg, and pack up and go home
	if (gameManager) {
		if (!gameManager->OnCreate()) {
			Debug::FatalError("Failed to initialize Game Manager.", "Engine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	//print log msg if everything worked with Debug::OnCreate
	Debug::Info("OnCreate initialized correctly.", "Engine.cpp", __LINE__);

	//make sure to start timer, has to be last thing we do.
	timer.Start();

	//if OnCreate works, set isRunning to true
	return isRunning = true;
}

void Engine::Run() {
	//while isRunning is true, continuously call Update/Render
	while (isRunning) {
		//update our previous and current ticks
		timer.UpdateFrameTicks();
		
		//update -- this number is 60FPS
		Update(timer.GetDeltaTime());
		Render();
		
		//delay our update until sleep time has finished, based on our fps value
		SDL_Delay(timer.GetSleepTime(fps));
	}
	
	//when isRunning is false, pack up and go home
	OnDestroy();
}

//exit function -- close the program
void Engine::Exit() { isRunning = false; }

//update our window
void Engine::Update(const float deltaTime_) {
	if (gameManager) { 
		gameManager->Update(deltaTime_); 
	}
}

/*Render the window
	1. set color to black
	2. clear the buffer bit and depth bit
	//RENDER EVERYTHING FOR THE GAME//
	3. call the game render
*/
void Engine::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//call game render	
	if (gameManager) gameManager->Render();

	SDL_GL_SwapWindow(window->GetWindow());
}

/*clean up our stuffs
	1. delete window / nullptr
	2. call SDL_Quit - close out entire proj
	3. call exit(0) to finalize exit. Exit the entire program
*/
void Engine::OnDestroy() {
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();

	delete gameManager;
	gameManager = nullptr;
	
	delete window;
	window = nullptr;

	delete camera;
	camera = nullptr;

	SDL_Quit();
	exit(0);
}
