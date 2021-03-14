#include "LightSource.h"

LightSource::LightSource(vec3 position_, float ambientVal_, float diffuseVal_, float specularVal_, vec3 lightColour_) 
	: position(vec3()), ambientVal(0.0f), diffuseVal(0.0f), specularVal(0.0f), lightColour(vec3()) {
	position = position_;
	ambientVal = ambientVal_;
	diffuseVal = diffuseVal_;
	specularVal = specularVal_;
	lightColour = lightColour_;
}

LightSource::~LightSource() {}
