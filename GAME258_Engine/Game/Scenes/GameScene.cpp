#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {

}

bool GameScene::OnCreate() {
	Debug::Info("Game Scene created.", "GameScene.cpp", __LINE__);
	
	Engine::GetInstance()->SetCamera(new Camera());
	Engine::GetInstance()->GetCamera()->SetPosition(vec3(0.0f, 0.0f, 4.0f));
	Engine::GetInstance()->GetCamera()->AddLightSources(new LightSource(vec3(0.0, 0.0, 2.0), 0.1f, 0.5f, 0.5f, vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();

	//create our model ref and add the mesh to our new model
	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	

	//model->SetScale(vec3(0.5f));

	//create the game object with our assosciated mesh
	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, vec3(-2.0f, 0.0f, -2.0f)));
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, vec3(1.5f, 0.0f, 0.0f)), "Apple");

	diceModel = nullptr;
	appleModel = nullptr;

	return true;
}

void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render() {
	SceneGraph::GetInstance()->Render(Engine::GetInstance()->GetCamera());
}
