#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

class Model {
public:
	Model(GLuint shaderProgram_, vec3 position_ = vec3(), float angle = 0.0f, vec3 rotation_ = vec3(0.0f, 1.0f, 0.0f), vec3 scale_ = vec3(1.0f));
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	inline void SetPosition(vec3 position_) { position = position_; }
	inline vec3 GetPosition() const { return position; }

	inline void SetRotation(vec3 rotation_) { rotation = rotation_; }
	inline vec3 GetRotaion() const { return rotation; }

	inline void SetScale(vec3 scale_) { scaleVar = scale_; }
	inline vec3 SetScale() const { return scaleVar; }

	inline void SetAngle(float angle_) { angle = angle_; }
	inline float GetAngle() const { return angle; }

private:
	vector<Mesh*> meshes;
	GLuint shaderProgram;

	vec3 position, rotation, scaleVar;
	float angle;

	mat4 GetTransform() const;
};
#endif

