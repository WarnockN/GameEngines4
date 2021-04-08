#include "GameScene.h"

GameScene::GameScene() : gObject(nullptr) {
}

GameScene::~GameScene() {
	model = nullptr;
	
	delete gObject;
	gObject = nullptr;
}

bool GameScene::OnCreate() {
	Debug::Info("Game Scene created.", "GameScene.cpp", __LINE__);
	
	Engine::GetInstance()->SetCamera(new Camera());
	Engine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.0f, 4.0f));
	Engine::GetInstance()->GetCamera()->AddLightSources(new LightSource(vec3(0.0, 0.0, 2.0), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	//create our model ref and add the mesh to our new model
	model = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	

	//model->SetScale(vec3(0.5f));

	//create the game object with our assosciated mesh
	gObject = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_) {
	gObject->Update(deltaTime_);
}

void GameScene::Render() {
	gObject->Render(Engine::GetInstance()->GetCamera());
}
