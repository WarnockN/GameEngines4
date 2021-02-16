#include "GameScene.h"

GameScene::GameScene() : gObject(nullptr) {
}

GameScene::~GameScene() {
	delete gObject;
	gObject = nullptr;
}

bool GameScene::OnCreate() {
	Debug::Info("Game Scene created.", "GameScene.cpp", __LINE__);
	cout << "Game Scene" << endl;
	//create our vertex ref and our vertexList ref, make sure to reserve the number of elements that you need
	Vertex v;
	vector<Vertex> vertexList;
	vertexList.reserve(3);

	//create the verticies for our triangle
	v.position = vec3(0.0f, 0.5f, 0.0f);
	v.colour = vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = vec3(-0.5f, -0.5f, 0.0f);
	v.colour = vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	v.position = vec3(0.5f, -0.5f, 0.0f);
	v.colour = vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	//triangle 2
	/*v.position = vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);*/

	//create our model ref and add the mesh to our new model
	Model* model = new Model(ShaderHandler::GetInstance()->GetShader("colourShader"));
	model->AddMesh(new Mesh(vertexList));
	
	//create the game object with our assosciated mesh
	gObject = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_) {
}

void GameScene::Render() {
	gObject->Render();
}
