#include "CollisionHandler.h"
#include "../Core/Engine.h"

unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
vector<GameObject*> CollisionHandler::prevCollisions = vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler() {
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

void CollisionHandler::OnCreate(float worldSize_) {
	prevCollisions.clear();

	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::OnDestroy() {
	delete scenePartition;
	scenePartition = nullptr;
	
	for (auto entry : prevCollisions) entry = nullptr;
	prevCollisions.clear();
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) collisionInstance.reset(new CollisionHandler);

	return collisionInstance.get();
}

void CollisionHandler::AddObject(GameObject* gObject_) {
	if (scenePartition != nullptr) scenePartition->AddObject(gObject_);
}

void CollisionHandler::MouseUpdate(vec2 mousePos_, int buttonType_) {
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos_,
		Engine::GetInstance()->GetScreenWidth(),
		Engine::GetInstance()->GetScreenHeight(),
		Engine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);
		
		if (hitResult) hitResult->SetHit(true, buttonType_);

		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) c->SetHit(false, buttonType_);
			c = nullptr;
		}
		prevCollisions.clear();


		if (hitResult) prevCollisions.push_back(hitResult);
	}
}
	



