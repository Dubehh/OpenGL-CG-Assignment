#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "worldloader.h"
#include "camera.h"

using namespace std;
GLuint programID;
mat4 projection;

const int width = 1200,
		  height = 900;

Camera* camera = new Camera(width, height);
WorldLoader* world = new WorldLoader();

void render() {
	glClearColor(0.0, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->draw(camera->getView(), projection, programID);
	if (camera->isFirstPerson())
		glutWarpPointer(width / 2, height / 2);
	glutSwapBuffers();
}

void render(int) {
	render();
	glutTimerFunc(10, render, 0);
}

void onKeyEvent(unsigned char key, int x, int y) {
	camera->onKeyEvent(key);
}

void onMouseEvent(int x, int y) {
	camera->onMouseEvent(x, y);
}

void initCore(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Final Assignment");
	glutDisplayFunc(render);
	glewInit();
}

void initShader() {
	GLuint fshID = glsl::makeFragmentShader(glsl::readFile("fragmentshader.fsh"));
	GLuint vshID = glsl::makeVertexShader(glsl::readFile("vertexshader.vsh"));
	programID = glsl::makeShaderProgram(vshID, fshID);
	projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 500.0f);
}

void initWorld() {
	world->createWorld();
	world->load(programID, projection);
}


int main(int argc, char ** argv) {
	initCore(argc, argv);
	initShader();
	initWorld();
	
	glutKeyboardFunc(onKeyEvent);
	glutPassiveMotionFunc(onMouseEvent);

	glutTimerFunc(10, render, 0);
	glutMainLoop();
	return 0;
}


