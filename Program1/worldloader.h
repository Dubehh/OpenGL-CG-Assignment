#include "model.h"

#pragma once
class WorldLoader {
private:
	vector<Model *> models;
public:
	~WorldLoader();
	void enlist(Model*);
	void load(GLuint, const mat4&);
	void createWorld();
	void draw(const mat4&, const mat4&, GLuint);
};

