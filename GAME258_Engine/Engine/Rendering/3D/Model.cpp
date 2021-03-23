#include "Model.h"


Model::Model(const string& objPath_, const string& matPath_, GLuint shaderProgram_)
: meshes(vector<Mesh*>()), shaderProgram(0), modelInstances(vector<mat4>()) {
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

void Model::Render(Camera* camera_) {
	glUseProgram(shaderProgram);

	for (auto m : meshes) m->Render(camera_, modelInstances);
}

void Model::AddMesh(Mesh* mesh_) {
	meshes.push_back(mesh_);
}

unsigned int Model::CreateInstance(vec3 position_, float angle_, vec3 rotation_, vec3 scale_) {
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, vec3 position_, float angle_, vec3 rotation_, vec3 scale_) {
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstances[index_];
}

mat4 Model::CreateTransform(vec3 position_, float angle_, vec3 rotation_, vec3 scale_) const {
	mat4 model;
	model = translate(model, position_);
	model = rotate(model, angle_, rotation_);
	model = scale(model, scale_);
	return model;
}

void Model::LoadModel() {

}
