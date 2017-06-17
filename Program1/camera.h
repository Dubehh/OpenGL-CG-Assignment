
#include <GL/glew.h>
#include <GL/freeglut.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
#pragma once
class Camera {
private:
	float
		sensivity = 0.005f,
		speed = 1,
		horizontalOffset = 4.4f,
		verticalOffset = 0;

	bool firstPersonPerspective = false;
	vec3 position;
	int width, height, x, y;
	void onFirstPersonControlling(unsigned char key);
	void perspectiveChangedEvent();
public:
	void togglePerspective();
	bool isFirstPerson();
	mat4 getView();
	vec3 getDirection();
	vec3 getRight();
	vec3 targetDirection();
	void onMouseEvent(int x, int y);
	void onKeyEvent(unsigned char key);
	Camera(int,int);
};

