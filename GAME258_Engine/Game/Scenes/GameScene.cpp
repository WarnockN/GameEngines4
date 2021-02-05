#include "GameScene.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

bool GameScene::OnCreate() {
	Debug::Info("Game Scene.", "GameScene.cpp", __LINE__);
	cout << "Game Scene" << endl;
	return true;
}

void GameScene::Update(const float deltaTime_) {
	cout << deltaTime_ << endl;
}

void GameScene::Render() {
}
