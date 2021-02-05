#include "StartScene.h"

StartScene::StartScene() {
}

StartScene::~StartScene() {
}

bool StartScene::OnCreate() {
	Debug::Info("Sart Scene.", "StartScene.cpp", __LINE__);
	cout << "StartScene" << endl;
	return true;
}

void StartScene::Update(const float deltaTime_) {
	if (SDL_PollEvent(&event)) {
		switch (event.key.keysym.sym) {
		case SDLK_1:
			Engine::GetInstance()->SetCurrentScene(1);
			break;
		default:
			break;
		}
	}
}

void StartScene::Render() {
}
