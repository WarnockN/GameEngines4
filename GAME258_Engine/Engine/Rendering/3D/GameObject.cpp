#include "GameObject.h"

GameObject::GameObject(Model* model_) 
	: model(nullptr), position(vec3()), rotation(vec3(0.0f, 1.0f, 0.0f)), scaleVar(vec3(1.0f)), angle(0.0f), modelInstance(0) {
	model = model_;
	if (model) modelInstance = model->CreateInstance(position, angle, rotation, scaleVar);
}

GameObject::GameObject(Model* model_, vec3 position_) 
	: model(nullptr), position(vec3()), rotation(vec3(0.0f, 1.0f, 0.0f)), scaleVar(vec3(1.0f)), angle(0.0f), modelInstance(0) {
	model = model_;
	position = position_;
	if (model) modelInstance = model->CreateInstance(position, angle, rotation, scaleVar);
}

GameObject::~GameObject() {
	model = nullptr;
}

void GameObject::Update(const float deltaTime_) {
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_) {
	if (model) model->Render(camera_);
}

void GameObject::SetPosition(vec3 position_) {
	position = position_;
	if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scaleVar);
}

void GameObject::SetRotation(vec3 rotation_) {
	rotation = rotation_;
	if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scaleVar);
}

void GameObject::SetScale(vec3 scaleVar_) {
	scaleVar = scaleVar_;
	if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scaleVar);
}

void GameObject::SetAngle(float angle_) {
	angle = angle_;
	if (model) model->UpdateInstance(modelInstance, position, angle, rotation, scaleVar);
}
