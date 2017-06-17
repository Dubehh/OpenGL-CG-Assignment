#include "model.h"

#pragma once
class WorldLoader {
private:
	std::vector<Model *> models;
public:
	~WorldLoader();
	void enlist(Model*);
	void load(GLuint programID, const glm::mat4 &projection);
	void createWorld();
	void draw(const mat4&, const mat4&, GLuint);
};

