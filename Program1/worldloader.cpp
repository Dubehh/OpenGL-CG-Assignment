#include "worldloader.h"

/* Material definitions*/
const Material shiny = Material(vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f);
const Material clean = Material(vec3(0.5f, 0.5f, 0.5f), vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), 10.0f);

/* Models that are animated */
Model * ball = NULL;
Model * tank = NULL;
Model * millTop = NULL;

/* Initialize some trees */
void WorldLoader::initTrees() {
	for (int i = 0; i < 3; i++) {
		Model* tree = new Model("Models/tree.obj", "Textures/tree.bmp");
		tree->move(vec3(i*3, 0, 5));
		tree->setMaterial(clean);
		enlist(tree);
	}	
}

/* Initialize all leftover models */
void WorldLoader::initMisc() {
	Model* crate = new Model("Models/box.obj", "Textures/crate.bmp");
	crate->move(vec3(2, 0, 2));
	enlist(crate);

	Model* barrel = new Model("Models/barrel.obj", "Textures/barrel.bmp");
	barrel->move(vec3(1.6f, 0, 2));
	enlist(barrel);

	ball = new Model("Models/ball.obj", "Textures/ball.bmp");
	ball->move(vec3(1, .2f, 4));
	enlist(ball);

	Model* bucket = new Model("Models/bucket.obj", "Textures/bucket.bmp");
	bucket->move(vec3(2, .05f, .4));
	enlist(bucket);

	tank = new Model("Models/tank.obj", "Textures/camo.bmp");
	tank->move(vec3(7, 0, 8));
	tank->setMaterial(clean);
	enlist(tank);
}

/* Initialize all structures */
void WorldLoader::initBuilding() {
	Model* house = new Model("Models/tent.obj", "Textures/cloth.bmp");
	enlist(house);

	Model* toilet = new Model("Models/toilet.obj", "Textures/crate.bmp");
	toilet->move(vec3(-4, 0, 0));
	enlist(toilet);

	Model* millBase = new Model("Models/millBase.obj", "Textures/metal.bmp");
	millBase->move(vec3( -6, 0, 4));
	enlist(millBase);

	millTop = new Model("Models/millTop.obj", "Textures/metal.bmp");
	millTop->move(millBase->position + vec3(0, 7, 0));
	enlist(millTop);

}

/* Initialize the ground models */
void WorldLoader::initGround() {
	enlist(new Model("Models/ground.obj", "Textures/grass.bmp"));
	Model* road = new Model("Models/road.obj", "Textures/road.bmp");
	enlist(road->move(vec3(0, .01, 7)));
}

/* Delete pointers */
WorldLoader::~WorldLoader() {
	int size = this->models.size();
	for (int i = size - 1; i > 0; i--)
		delete this->models[i];
}

/* Add an object to the world */
void WorldLoader::enlist(Model * model) {
	this->models.push_back(model);
}

/* Load all objects and load their buffers */
void WorldLoader::load(GLuint id, const mat4& projection) {
	glBindVertexArray(0);
	glUseProgram(id);
	for (auto &model : models) {
		model->load();
		model->loadBuffer(id, projection);
	}
	glUseProgram(0);
}

/* Initialize the world */
void WorldLoader::createWorld() {
	this->initTrees();
	this->initBuilding();
	this->initMisc();
	this->initGround();

}

/* Draw the world */
void WorldLoader::draw(const mat4 &view, const mat4&projection, GLuint id) {
	this->animate();
	for (auto &model : this->models)
		model->draw(view, projection, id);
}

float ballSpeed = 0.05f;
float tankSpeed = 0.03f;
/* Animate models if needed */
void WorldLoader::animate() {
	if (ball->position.y < .25f) ballSpeed = 0.05f;
	else if (ball->position.y > 1.5) ballSpeed *= -1;
	ball->move(vec3(0, ballSpeed, 0));

	if (tank->position.x > 7) tankSpeed = 0.03f;
	else if (tank->position.x < -7) tankSpeed *= -1;
	tank->move(vec3(-1*tankSpeed, 0, 0));
	millTop->rotate(0.05f, vec3(1, 0, 0));

}

