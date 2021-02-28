#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera {
public:
	Camera();
	~Camera();

	inline void SetPosition(vec3 position_) { position = position_;
											  UpdateCameraVectors(); }

	inline vec3 GetPosition() const { return position; }

	inline void SetRotation(float yaw_, float pitch_) { yaw = yaw_;
														pitch = pitch_;
														UpdateCameraVectors(); }

	inline mat4 GetView() const { return view; }
	inline mat4 GetPerspective() const { return perspec; }
	inline mat4 GetOrthograpic() const { return orthographic; }

private:
	void UpdateCameraVectors();
	vec3 position;
	mat4 perspec, orthographic, view;
	float fov;
	float yaw, pitch;
	float nearPlane, farPlane;
	vec3 forward, up, right, worldUp;
};
#endif

