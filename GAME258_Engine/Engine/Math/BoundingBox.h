#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../Core/Camera.h"

using namespace glm;

struct BoundingBox {
	vec3 maxVert, minVert;
	mat4 transform;

	inline BoundingBox() {
		maxVert = minVert = vec3();
		transform = mat4();
	}

	inline BoundingBox(vec3 maxVert_, vec3 minVert_, mat4 transform_) {
		maxVert = maxVert_;
		minVert = minVert_;
		transform = transform_;
	}

	inline int TestIntersection(Camera* camera_) {
		vec4* planes = camera_->ExtractFrustumPlanes();

		int result = 0;

		for (uint i = 0; i < 6; i++) {
			const float pos = planes[i].w;
			const vec3 normal = vec3(planes[i]);

			if (dot(normal, GetPositiveVertex(normal)) + pos < 0.0f) return 1;

			if (dot(normal, GetNegativeVertex(normal)) + pos < 0.0f) return 2;
		}

		return result;
	}

	inline vec3 GetPositiveVertex(const vec3& normal) const
	{
		vec3 positiveVertex = minVert;

		if (normal.x >= 0.0f) positiveVertex.x = maxVert.x;
		if (normal.y >= 0.0f) positiveVertex.y = maxVert.y;
		if (normal.z >= 0.0f) positiveVertex.z = maxVert.z;

		return positiveVertex;
	}

	inline vec3 GetNegativeVertex(const vec3& normal) const
	{
		vec3 negativeVertex = maxVert;

		if (normal.x >= 0.0f) negativeVertex.x = minVert.x;
		if (normal.y >= 0.0f) negativeVertex.y = minVert.y;
		if (normal.z >= 0.0f) negativeVertex.z = minVert.z;

		return negativeVertex;
	}
};

#endif
