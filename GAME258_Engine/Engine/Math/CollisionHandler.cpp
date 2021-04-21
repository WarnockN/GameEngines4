#include "CollisionHandler.h"
#include "../Core/Engine.h"

unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
vector<GameObject*> CollisionHandler::prevCollisions = vector<GameObject*>();
vector<GameObject*> CollisionHandler::colliders = vector<GameObject*>();

CollisionHandler::CollisionHandler() {
	colliders.reserve(10);
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

void CollisionHandler::OnCreate() {
	colliders.clear();
	prevCollisions.clear();
}

void CollisionHandler::OnDestroy() {
	for (auto entry : colliders) entry = nullptr;
	colliders.clear();

	for (auto entry : prevCollisions) entry = nullptr;
	prevCollisions.clear();
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) collisionInstance.reset(new CollisionHandler);

	return collisionInstance.get();
}

void CollisionHandler::AddObject(GameObject* gObject_) {
	colliders.push_back(gObject_);
}

void CollisionHandler::MouseUpdate(vec2 mousePos_, int buttonType_) {
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePos_,
		Engine::GetInstance()->GetScreenWidth(),
		Engine::GetInstance()->GetScreenHeight(),
		Engine::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDistance = FLT_MAX;

	for (auto g : colliders) {
		if (mouseRay.IsColliding(&g->GetBoundingBox())) {
			if (mouseRay.intersectionDist < shortestDistance) {
				hitResult = g;
				shortestDistance = mouseRay.intersectionDist;
			}
		}
	}

	if (hitResult) hitResult->SetHit(true, buttonType_);

	for (auto c : prevCollisions) {
		if (hitResult != c && c != nullptr) c->SetHit(false, buttonType_);
	}

	prevCollisions.clear();
	if (hitResult) prevCollisions.push_back(hitResult);
}
	



