#include "Camera.h"

#include "../Core/Engine.h"

vector<LightSource*> Camera::lightSources = vector<LightSource*>();

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
	if (lightSources.size() > 0) {
		for (auto l : lightSources) {
			delete l;
			l = nullptr;
		}
		lightSources.clear();
	}
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

void Camera::ProcessMouseMovement(vec2 offset_) {
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	if (yaw < 0.0f) yaw += 0.0f;
	if (yaw > 360.0f) yaw -= 360.0f;

	UpdateCameraVectors();

}

void Camera::ProcessMouseZoom(int y_) {
	if (y_ < 0 || y_ > 0) position += static_cast<float>(y_) * (forward * 2.0f);
	
	UpdateCameraVectors();
}

vec4* Camera::ExtractFrustumPlanes() {
    const mat4& v = GetView();
    const mat4& p = GetPerspective();

    mat4 clipMatrix = v * p;
    vec4 planes[6];

    //set up each piece of the clip matrix
    /*{
        clipMatrix[0][0] = v[0][0] * p[0][0] + v[0][1] * p[1][0] + v[0][2] * p[2][0] + v[0][3] * p[3][0];
        clipMatrix[1][0] = v[0][0] * p[0][1] + v[0][1] * p[1][1] + v[0][2] * p[2][1] + v[0][3] * p[3][1];
        clipMatrix[2][0] = v[0][0] * p[0][2] + v[0][1] * p[1][2] + v[0][2] * p[2][2] + v[0][3] * p[3][2];
        clipMatrix[3][0] = v[0][0] * p[0][3] + v[0][1] * p[1][3] + v[0][2] * p[2][3] + v[0][3] * p[3][3];
        clipMatrix[0][1] = v[1][0] * p[0][0] + v[1][1] * p[1][0] + v[1][2] * p[2][0] + v[1][3] * p[3][0];
        clipMatrix[1][1] = v[1][0] * p[0][1] + v[1][1] * p[1][1] + v[1][2] * p[2][1] + v[1][3] * p[3][1];
        clipMatrix[2][1] = v[1][0] * p[0][2] + v[1][1] * p[1][2] + v[1][2] * p[2][2] + v[1][3] * p[3][2];
        clipMatrix[3][1] = v[1][0] * p[0][3] + v[1][1] * p[1][3] + v[1][2] * p[2][3] + v[1][3] * p[3][3];
        clipMatrix[0][2] = v[2][0] * p[0][0] + v[2][1] * p[1][0] + v[2][2] * p[2][0] + v[2][3] * p[3][0];
        clipMatrix[1][2] = v[2][0] * p[0][1] + v[2][1] * p[1][1] + v[2][2] * p[2][1] + v[2][3] * p[3][1];
        clipMatrix[2][2] = v[2][0] * p[0][2] + v[2][1] * p[1][2] + v[2][2] * p[2][2] + v[2][3] * p[3][2];
        clipMatrix[3][2] = v[2][0] * p[0][3] + v[2][1] * p[1][3] + v[2][2] * p[2][3] + v[2][3] * p[3][3];
        clipMatrix[0][3] = v[3][0] * p[0][0] + v[3][1] * p[1][0] + v[3][2] * p[2][0] + v[3][3] * p[3][0];
        clipMatrix[1][3] = v[3][0] * p[0][1] + v[3][1] * p[1][1] + v[3][2] * p[2][1] + v[3][3] * p[3][1];
        clipMatrix[2][3] = v[3][0] * p[0][2] + v[3][1] * p[1][2] + v[3][2] * p[2][2] + v[3][3] * p[3][2];
        clipMatrix[3][3] = v[3][0] * p[0][3] + v[3][1] * p[1][3] + v[3][2] * p[2][3] + v[3][3] * p[3][3];
    }*/

    //set each axis of each plane
    {
        planes[PLANE_RIGHT].x = clipMatrix[3][0] - clipMatrix[0][0];
        planes[PLANE_RIGHT].y = clipMatrix[3][1] - clipMatrix[0][1];
        planes[PLANE_RIGHT].z = clipMatrix[3][2] - clipMatrix[0][2];
        planes[PLANE_RIGHT].w = clipMatrix[3][3] - clipMatrix[0][3];

        planes[PLANE_LEFT].x = clipMatrix[3][0] + clipMatrix[0][0];
        planes[PLANE_LEFT].y = clipMatrix[3][1] + clipMatrix[0][1];
        planes[PLANE_LEFT].z = clipMatrix[3][2] + clipMatrix[0][2];
        planes[PLANE_LEFT].w = clipMatrix[3][3] + clipMatrix[0][3];

        planes[PLANE_BOTTOM].x = clipMatrix[3][0] + clipMatrix[1][0];
        planes[PLANE_BOTTOM].y = clipMatrix[3][1] + clipMatrix[1][1];
        planes[PLANE_BOTTOM].z = clipMatrix[3][2] + clipMatrix[1][2];
        planes[PLANE_BOTTOM].w = clipMatrix[3][3] + clipMatrix[1][3];

        planes[PLANE_TOP].x = clipMatrix[3][0] - clipMatrix[1][0];
        planes[PLANE_TOP].y = clipMatrix[3][1] - clipMatrix[1][1];
        planes[PLANE_TOP].z = clipMatrix[3][2] - clipMatrix[1][2];
        planes[PLANE_TOP].w = clipMatrix[3][3] - clipMatrix[1][3];

        planes[PLANE_BACK].x = clipMatrix[3][0] - clipMatrix[2][0];
        planes[PLANE_BACK].y = clipMatrix[3][1] - clipMatrix[2][1];
        planes[PLANE_BACK].z = clipMatrix[3][2] - clipMatrix[2][2];
        planes[PLANE_BACK].w = clipMatrix[3][3] - clipMatrix[2][3];

        planes[PLANE_FRONT].x = clipMatrix[3][0] + clipMatrix[2][0];
        planes[PLANE_FRONT].y = clipMatrix[3][1] + clipMatrix[2][1];
        planes[PLANE_FRONT].z = clipMatrix[3][2] + clipMatrix[2][2];
        planes[PLANE_FRONT].w = clipMatrix[3][3] + clipMatrix[2][3];
    }

    //normalize planes
    for (int i = 0; i < 6; i++) {
        planes[i] = normalize(planes[i]);
    }

    return planes;
}
