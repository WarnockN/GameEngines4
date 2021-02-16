#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameManager.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"



using namespace std;

class Engine {
public:
	/*to create a Singleton style engine we need to write these 4 lines of code
	//THEY ENSURE THAT THERE ARE NO COPY OR MOVE CONSTRUCTORS//
	any cope of move constructors of this class we get an error if attempted. 
	we are using SMART POINTERS to do this

	lastly, we move our constructor and destructor to private
	*/
	Engine(const Engine&) = delete;
	Engine(Engine&&) = delete;
	Engine& operator=(const Engine&) = delete;
	Engine& operator=(Engine&&) = delete;

	static Engine* GetInstance();

	
	bool OnCreate(string name_, int width_, int height_);
	void Run();
	void Exit();

	//getters and setters
	inline bool GetIsRunning() const { return isRunning; }

	inline void SetGameManager(GameManager* gameManager_) { gameManager = gameManager_; }

	inline int GetCurrentScene() const { return currentSceneNum; }
	inline void SetCurrentScene(int sceneNum_) { currentSceneNum = sceneNum_; }

private:
	Engine();
	~Engine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	/*this unique ptr will automatically delete itself when it goes out of scope (IE: when  proj ends)
	we use the default delete to ask HOW we want the pointer to be deleted. Default delete calls the destructor.
	Make sure to friend this so we are able to see the destructor as it is now PRIVATE
	*/
	static unique_ptr<Engine> engineInstance;
	friend default_delete<Engine>;

	Window* window;
	bool isRunning;
	
	Timer timer;
	unsigned int fps;

	GameManager* gameManager;

	int currentSceneNum;


};
#endif
