#include "model.h"

#pragma once
class WorldLoader {
private:
	std::vector<Model *> models;
	void initTrees();
	void initMisc();
	void initBuilding();
	void initGround();
public:
	~WorldLoader();
	void enlist(Model*);
	void load(GLuint programID, const glm::mat4 &projection);
	void createWorld();
	void draw(const mat4&, const mat4&, GLuint);
	void animate();
};

