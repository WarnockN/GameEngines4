#include "Camera.h"

#include "../Core/Engine.h"

Camera::Camera() : position(vec3()), fov(0.0f), forward(vec3()), up(vec3()), right(vec3()), worldUp(vec3()), 
				   nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), perspec(mat4()), orthographic(mat4()), view(mat4()) {
	fov = 45.0f;
	forward = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspec = perspective(fov,
		Engine::GetInstance()->GetScreenWidth() / Engine::GetInstance()->GetScreenHeight(), 
		nearPlane, farPlane);

	orthographic = ortho(0.0f, Engine::GetInstance()->GetScreenWidth(),
						 0.0f, Engine::GetInstance()->GetScreenHeight(),
						 -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera() {
}

void Camera::UpdateCameraVectors() {
	forward.x = cos(radians(yaw)) * cos(radians(pitch));
	forward.y = sin(radians(pitch));
	forward.z = sin(radians(yaw)) * cos(radians(pitch));

	forward = normalize(forward);
	right = normalize(cross(forward, worldUp));
	up = normalize(cross(right, forward));
	view = lookAt(position, position + forward, up);
}