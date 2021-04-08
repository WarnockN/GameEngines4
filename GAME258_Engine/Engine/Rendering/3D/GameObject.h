#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"

using namespace glm;

class GameObject {
public:
	GameObject(Model* model_);
	GameObject(Model* model_, vec3 position_);
	~GameObject();

	void Update(const float deltaTime_);
	void Render(Camera* camera_);

	void SetPosition(vec3 position_);
	inline vec3 GetPosition() const { return position; }

	void SetRotation(vec3 rotation_);
	inline vec3 GetRotaion() const { return rotation; }

	void SetScale(vec3 scaleVar_);
	inline vec3 SetScale() const { return scaleVar; }

	void SetAngle(float angle_);
	inline float GetAngle() const { return angle; }

	inline void SetTag(string tag_) { tag = tag_; }
	inline string GetTag() const { return tag; }


private:
	Model* model;
	unsigned int modelInstance;
	vec3 position, rotation, scaleVar;
	float angle;
	string tag;
};
#endif

