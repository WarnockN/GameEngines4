#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"

using namespace std;

class CollisionHandler {
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();

	void OnCreate();
	void AddObject(GameObject* gObject_);
	void MouseUpdate(vec2 mousePos_, int buttonType_);
	void OnDestroy();

private:
	CollisionHandler();
	~CollisionHandler();

	static unique_ptr<CollisionHandler> collisionInstance;
	friend default_delete<CollisionHandler>;

	static vector<GameObject*> colliders;
	static vector<GameObject*> prevCollisions;

};
#endif

