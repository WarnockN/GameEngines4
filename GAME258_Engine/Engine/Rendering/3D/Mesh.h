#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Core/Camera.h"
#include "../../Graphics/MaterialHandler.h"

using namespace glm;
using namespace std;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 textureCoordinates;
};

struct SubMesh {
	vector<Vertex> vertexList;
	vector<unsigned int> meshIndices;
	Material material;
};

class Mesh {
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, vector<mat4> instances_);

private:
	void GenerateBuffers();
	/*VAO = Vertex Array Object // tells GPU how we store our vertex data
	  VBO = Vertex Buffer Objects // buffer that provides the ways to push data to the GPU*/
	GLuint VAO, VBO;
	vector<Vertex> vertexList;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint lightPosition, ambientValue, diffuseValue, specularValue, lightColour;
	GLuint modelLoc, viewLoc, projLoc, textureLoc, cameraLoc;

	SubMesh subMesh;
};
#endif

