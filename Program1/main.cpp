#include <iostream>
#include <vector>

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

const char * FSH = "fragmentshader.fsh";
const char * VSH = "vertexshader.vsh";

const int width = 1200,
		  height = 900;

Camera* camera = new Camera(width, height);
WorldLoader* world = new WorldLoader();

void render() {
	glClearColor(0.0, 0.0, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->draw(camera->getView(), projection, programID);
	glutSwapBuffers();

	if (camera->isFirstPerson())
		glutWarpPointer(width / 2, height / 2);
}

void render(int n) {
	render();
	glutTimerFunc(10, render, 0);
}

//void loadShader() {
//	GLuint fshID = glsl::makeFragmentShader(glsl::readFile("fragmentshader.fsh"));
//	GLuint vshID = glsl::makeVertexShader(glsl::readFile("vertexshader.vsh"));
//	programID = glsl::makeShaderProgram(vshID, fshID);
//}

void onKeyEvent(unsigned char key, int x, int y) {
	camera->onKeyEvent(key);
}

void onMouseEvent(int x, int y) {
	camera->onMouseEvent(x, y);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(width, height);
	glutCreateWindow("Hello OpenGL");

	glutDisplayFunc(render);

	glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initialized the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
	char * fragshader = glsl::readFile(FSH);
	GLuint fshID = glsl::makeFragmentShader(fragshader);

	char * vertexshader = glsl::readFile(VSH);
	GLuint vshID = glsl::makeVertexShader(vertexshader);

	programID = glsl::makeShaderProgram(vshID, fshID);
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------


void InitMatrices()
{
	projection = glm::perspective(45.0f,
		1.0f * width / height, 0.1f,
		200.0f);
}

//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
	//Loop through all the objects in our vector and init the buffers
	world->initBuffers(programID, projection);

}


int main(int argc, char ** argv) {

	InitGlutGlew(argc, argv);
	InitShaders();
	InitMatrices();
	world->createWorld();
	InitBuffers();
	glUseProgram(programID);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	HWND hWnd = GetConsoleWindow();

	//leave this for debug purposes
	//ShowWindow(hWnd, SW_HIDE);

	glutKeyboardFunc(onKeyEvent);
	glutPassiveMotionFunc(onMouseEvent);
	glutTimerFunc(10, render, 0);
	glutMainLoop();



/*
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Final Assignment");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glutDisplayFunc(render);
	glewInit();

	projection = glm::perspective(45.0f, 1.0f * width / height, 0.1f, 200.0f);
	loadShader();

	world->createWorld();
	world->load(programID, projection);

	glutKeyboardFunc(onKeyEvent);
	glutPassiveMotionFunc(onMouseEvent);

	glutTimerFunc(10, render, 0);
	glutMainLoop();*/
	return 0;
}


