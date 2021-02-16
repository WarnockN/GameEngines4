#include "Model.h"

Model::Model(GLuint shaderProgram_) : meshes(vector<Mesh*>()), shaderProgram(0) {
	shaderProgram = shaderProgram_;
}

Model::~Model() {
	/*loop through ever element in the meshes array and delete it, and make sure its memory is deallocated correctly.
	
	  the auto keyword will "auto"matically (get it?) set the signature of this variable*/
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render() {
	glUseProgram(shaderProgram);

	for (auto m : meshes) m->Render(); 
}

void Model::AddMesh(Mesh* mesh_) {
	meshes.push_back(mesh_);
}
