#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

using namespace glm;
using namespace std;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 textureCoordinates;
	vec3 colour;
};

class Mesh {
public:
	Mesh(vector<Vertex>& vertexList_);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	/*VAO = Vertex Array Object // tells GPU how we store our vertex data
	  VBO = Vertex Buffer Objects // buffer that provides the ways to push data to the GPU*/
	GLuint VAO, VBO;
	vector<Vertex> vertexList;
};
#endif
