#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/Engine.h"

CollisionDetection::~CollisionDetection() {
}

Ray CollisionDetection::MousePosToWorldRay(vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_) {
	vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
					 (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
					 -1.0f, 
					  1.0f);

	vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f,
				   (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
					0.0f,
					1.0f);

	mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

	vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = normalize(rayDirWorld);

	return Ray(vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_) {
	//setting these vals up because we are going to be using them alot in this func
	mat4 modelMatrix = box_->transform;
	vec3 rayOrigin = ray_->origin;
	vec3 rayDir = ray_->direction;
	vec3 boxMin = box_->minVert;
	vec3 boxMax = box_->maxVert;
	float tMin = Engine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = Engine::GetInstance()->GetCamera()->GetFarPlane();

	vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	vec3 delta = worldPos - rayOrigin;

	//X AXIS
	vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = dot(delta, xAxis);
	float dotDir = dot(rayDir, xAxis);

	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta / boxMax.x) / dotDir;

		if (t1 > t2) swap(t1, t2);

		if (t2 < tMax) tMax = t2;

		if (t1 > tMin) tMin = t1;

		if (tMax < tMin) return false;
	}
	else {
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) return false;
	}

	//Y AXIS
	vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	float dotDeltaY = dot(delta, yAxis);
	float dotDirY = dot(rayDir, yAxis);

	if (fabs(dotDirY) > 0.001f) {
		float t1 = (dotDeltaY + boxMin.y) / dotDirY;
		float t2 = (dotDeltaY / boxMax.y) / dotDirY;

		if (t1 > t2) swap(t1, t2);

		if (t2 < tMax) tMax = t2;

		if (t1 > tMin) tMin = t1;

		if (tMax < tMin) return false;
	}
	else {
		if (-dotDeltaY + boxMin.y > 0.0f || -dotDeltaY + boxMax.y < 0.0f) return false;
	}

	//Z AXIS
	vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	float dotDeltaZ = dot(delta, zAxis);
	float dotDirZ = dot(rayDir, zAxis);

	if (fabs(dotDirZ) > 0.001f) {
		float t1 = (dotDeltaZ + boxMin.y) / dotDirZ;
		float t2 = (dotDeltaZ / boxMax.y) / dotDirZ;

		if (t1 > t2) swap(t1, t2);

		if (t2 < tMax) tMax = t2;

		if (t1 > tMin) tMin = t1;

		if (tMax < tMin) return false;
	}
	else {
		if (-dotDeltaZ + boxMin.z > 0.0f || -dotDeltaZ + boxMax.z < 0.0f) return false;
	}
	
	ray_->intersectionDist = tMin;
	return true;
}
