#include "model.h"

bool Model::hasComponents() {
	return this->components.size() > 0;
}

Model::Model(char* filePath, char* texturePath){
	this->filePath = filePath;
	this->texturePath = texturePath;
	this->mat = Material();
}


Model::~Model() {
	int size = this->components.size();
	for (int i = size - 1; i > 0; i--)
		delete this->components[i];
}

void Model::setMaterial(Material mat) {
	this->mat = mat;
}

void Model::addComponent(Model* model) {
	this->components.push_back(model);
}

void Model::load() {
	if (this->filePath == NULL) {
		this->isLoaded = true;
	} else {
		loadOBJ(this->filePath,
			vertices,
			uvs,
			normals);
		if (this->texturePath != NULL)
			this->texture = loadBMP(this->texturePath);
		this->isLoaded = true;
	}
}

void Model::loadBuffer(GLuint id, const mat4 &projection) {
	if (hasComponents())
		for (auto &component : this->components)
			component->loadBuffer(id, projection);
	else {
		/* setup vertices */
		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3),
			&vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		/* setup normals */
		glGenBuffers(1, &vbo_normals);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3),
			&normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		/* setup uvs */
		glGenBuffers(1, &vbo_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec2),
			&uvs[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		/* Initializing position attribute */
		GLuint attribute_position = glGetAttribLocation(id, "position");
		glEnableVertexAttribArray(attribute_position);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glVertexAttribPointer(
			attribute_position,
			3,
			GL_FLOAT, GL_FALSE,
			0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		/* Initializing normal attribute*/
		GLuint attribute_normals = glGetAttribLocation(id, "normal");
		glEnableVertexAttribArray(attribute_normals);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glVertexAttribPointer(
			attribute_normals,
			3,
			GL_FLOAT, GL_FALSE,
			0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		/* Initializing uvs attribute */
		GLuint attribute_uvs = glGetAttribLocation(id, "vertexUV");
		glEnableVertexAttribArray(attribute_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glVertexAttribPointer(
			attribute_uvs,
			2,
			GL_FLOAT, GL_FALSE,
			0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Model::draw(const mat4 &view, const mat4 &projection, GLuint programID) {
	if (!isLoaded) return;
	if (hasComponents())
		for (auto &component : this->components)
			component->draw(view, projection, programID);
	else {
		uniform_mv = glGetUniformLocation(programID, "mv");

		glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniform3fv(glGetUniformLocation(programID, "lightPos"), 1, glm::value_ptr(vec3(50, 50, 50)));
		glUniform3fv(glGetUniformLocation(programID, "matAmbient"), 1, value_ptr(mat.ambient));
		glUniform3fv(glGetUniformLocation(programID, "matDiffuse"), 1, value_ptr(mat.diffuse));
		glUniform3fv(glGetUniformLocation(programID, "matSpecular"), 1, value_ptr(mat.specular));
		glUniform1f(glGetUniformLocation(programID, "matPower"), mat.pow);

		mv = view * model;
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, value_ptr(mv));
		glBindVertexArray(vao);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
}

