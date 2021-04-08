#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

struct Light {
	vec3 lightPos;
	float ambient;
	float diffuse;
	float specular;
	vec3 lightCol;
};

uniform sampler2D inputTexture;
uniform vec3 cameraPos;
uniform Light light;

out vec4 fColour;

void main() {
	//ambient
	vec3 ambient = light.ambient * texture(inputTexture, TexCoords).rgb * light.lightCol;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * light.diffuse) * texture(inputTexture, TexCoords).rgb * light.lightCol;

	//specular
	vec3 viewDir = normalize(cameraPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	vec3 specular = (spec * light.specular) * light.lightCol;

	vec3 result = ambient + diffuse + specular;
	
	fColour = vec4(result, 1.0f);

}