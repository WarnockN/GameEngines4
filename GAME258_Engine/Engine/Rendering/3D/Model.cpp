#include "Model.h"

Model::Model() : meshes(vector<Mesh*>()) {

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
	for (auto m : meshes) m->Render();
}

void Model::AddMesh(Mesh* mesh_) {
	meshes.push_back(mesh_);
}
