#include "Mesh.h"

/*since VOA and VBO are uint, lowest numbers that it can go is 0
also set our vertex list to an empty vector -- hence enmpty brackets*/
Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) 
	: VAO(0), VBO(0), vertexList(vector<Vertex>()), shaderProgram(0), textureID(0), modelLoc(0), viewLoc(0), projLoc(0), textureLoc(0), cameraLoc(0), 
	lightPosition(0), ambientValue(0), diffuseValue(0), specularValue(0), lightColour(0) {
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

/*delete all our array's adresses and clear our list of verticies*/
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) subMesh.vertexList.clear();

	if (subMesh.meshIndices.size() > 0) subMesh.meshIndices.clear();
}

void Mesh::Render(Camera* camera_, vector<mat4> instances_) {
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(camera_->GetPerspective()));
	
	{
		glUniform3fv(cameraLoc, 1, value_ptr(camera_->GetPosition()));
		glUniform3fv(lightPosition, 1, value_ptr(camera_->GetLightSources()[0]->GetPosition()));
		glUniform1f(ambientValue, camera_->GetLightSources()[0]->GetAmbient());
		glUniform1f(diffuseValue, camera_->GetLightSources()[0]->GetDiffuse());
		glUniform1f(specularValue, camera_->GetLightSources()[0]->GetSpecular());
	}

	glBindVertexArray(VAO);

	//enable depth test, used for rendering. takes z axis into account.
	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++) { 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers() {
	//Generate and bind our VAO and VBO // open the locker door.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*1. set type of buffer to array buffer
	  2. set the size of the array to the number of vertex objects * the byte size
	  3. get the address of the first item in the array -- WE ARE ASSUMING THAT THE VERTEX IS FILLED IN BY DOING THIS. (AN OUT OF RANGE ERROR MAY OCCUR)
	  4. call static draw. change the data once, but use it multiple times. */
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);

	/*1. location of the attribute in the struct.
	  2. size of the vertex atribute. this is a vec3 sp 3 types of data in it
	  3. tell it that this is a float. (3 float values)
	  4. normalized? bool = false
	  5. specify the space between specificed vertex attribute sets. (when the gpu looks as the pos, it is going to jump x bytes to get the pos of the next vertex pos)
	  6. since this is first attrib, no need to offset anything here yet, see others for offset fucntion*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL 
	glEnableVertexAttribArray(1);

	/*for the offset, offsetof macro handles this
	pass in the struct type -- in this case Vertex, and then pass in the attribute that you want the offset of.*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//bind the vertex array and the buffer to 0 // close the locker door
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	cameraLoc - glGetUniformLocation(shaderProgram, "cameraPos");

	lightPosition = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambientValue = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuseValue = glGetUniformLocation(shaderProgram, "light.diffuse");
	specularValue = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightCol");
}

