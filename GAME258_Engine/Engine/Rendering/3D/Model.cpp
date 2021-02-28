#include "Model.h"


Model::Model(GLuint shaderProgram_, vec3 position_, float angle_, vec3 rotation_, vec3 scale_)
: meshes(vector<Mesh*>()), shaderProgram(0), position(vec3()), angle(0.0f), rotation(vec3(0.0f, 1.0f, 0.0f)), scale(vec3(1.0f)) {
	shaderProgram = shaderProgram_;
	position = position_;
	angle = angle_;
	rotation = rotation_;
	scale = scale_;
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

	for (auto m : meshes) m->Render(camera_, GetTransform()); 
}

void Model::AddMesh(Mesh* mesh_) {
	meshes.push_back(mesh_);
}

mat4 Model::GetTransform() const {
	mat4 model;

	model = translate(model, position);
	model = rotate(model, angle, rotation);
	model = glm::scale(model, scale);
	return model;
}
