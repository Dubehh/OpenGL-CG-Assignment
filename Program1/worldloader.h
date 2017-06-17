#include "model.h"

#pragma once
class WorldLoader {
private:
	std::vector<Model *> models;
public:
	~WorldLoader();
	void enlist(Model*);
	void initBuffers(GLuint programID, const glm::mat4 &projection);
	void load(GLuint, const mat4&);
	void createWorld();
	void draw(const mat4&, const mat4&, GLuint);
};

