#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/Engine.h"

using namespace std;
using namespace glm;

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	GameObject* gObject;
	Model* model;
};
#endif

