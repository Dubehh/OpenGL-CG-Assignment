#include "worldloader.h"


WorldLoader::~WorldLoader() {
	int size = this->models.size();
	for (int i = size - 1; i > 0; i--)
		delete this->models[i];
}

void WorldLoader::enlist(Model * model) {
	this->models.push_back(model);
}

void WorldLoader::load(GLuint id, const mat4& projection) {
	for (auto &model : this->models) {
		model->load();
		model->loadBuffer(id, projection);
	}
}

void WorldLoader::createWorld() {
	Model* box = new Model("Models/plane.obj", "Textures/grass.bmp");
	box->model = translate(box->model, box->position);
	enlist(box);
}

void WorldLoader::draw(const mat4 &view, const mat4&projection, GLuint id) {
	for (auto &model : this->models)
		model->draw(view, projection, id);
}

