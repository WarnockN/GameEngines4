#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class LightSource {
private:
	vec3 position;
	float ambientVal;
	float diffuseVal;
	float specularVal;
	vec3 lightColour;

public:
	LightSource(vec3 position_, float ambientVal_, float diffuseVal_, float specularVal_, vec3 lightColour_);
	~LightSource();

	inline void SetPosition(vec3 position_) { position = position_; }
	inline vec3 GetPosition() const { return position; }

	inline void SetAmbient(float ambientVal_) { ambientVal = ambientVal_; }
	inline float GetAmbient() const { return ambientVal; }

	inline void SetDiffuse(float diffuseVal_) { diffuseVal = diffuseVal_; }
	inline float GetDiffuse() const { return diffuseVal; }

	inline void SetSpecular(float specularVal_) { specularVal = specularVal_; }
	inline float GetSpecular() const { return specularVal; }

	inline void SetColour(vec3 lightColour_) { lightColour = lightColour_; }
	inline vec3 GetColour() const { return lightColour; }
};
#endif

