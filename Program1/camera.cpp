#include "camera.h"
#include <iostream>

#define ESCAPE 27
#define SPACEBAR 32

/* Listener used when the camera is in first person mode */
void Camera::onFirstPersonControlling(unsigned char key) {
	float momentum = .15f;
	switch (key) {
		case 'w': position += targetDirection() * momentum * speed; break;
		case 'a': position -= getRight() * momentum * speed; break;
		case 's': position -= targetDirection() * momentum * speed; break;
		case 'd': position += getRight() * momentum * speed; break;
	}
}

/* Toggles the camera perspective */
void Camera::togglePerspective() {
	this->firstPersonPerspective = !firstPersonPerspective;
	perspectiveChangedEvent();
}

/* Returns whether the camera is currently in firstperson mode */
bool Camera::isFirstPerson() {
	return this->firstPersonPerspective;
}

/* Returns the bounds of the current view perspective */
glm::mat4 Camera::getView() {
	vec3 right = getRight();
	vec3 dir = targetDirection();
	vec3 up = cross(right, dir);
	return lookAt(
		this->position,
		this->position + getDirection(),
		up
	);
}

/* Handler that fires when the camera changes perspective */
void Camera::perspectiveChangedEvent() {
	glutSetCursor(this->firstPersonPerspective ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
	this->position = this->firstPersonPerspective ? vec3(7, 1.5, 12) : vec3(8, 15, -8);
	if (!this->firstPersonPerspective) {
		horizontalOffset = 3.14f * -0.2f;
		verticalOffset = 3.14f * -0.2f;
	} else {
		horizontalOffset = 3.14f;
		verticalOffset = 0.0f;
	}
}

/* Returns the direction the camera is looking at */
vec3 Camera::getDirection() {
	return glm::vec3(
		cos(this->verticalOffset) * sin(this->horizontalOffset),
		sin(this->verticalOffset),
		cos(this->verticalOffset) * cos(this->horizontalOffset)
	);
}

vec3 Camera::getRight() {
	return glm::vec3(
		sin(this->horizontalOffset - 3.14f / 2.0f),
		0,
		cos(this->horizontalOffset - 3.14f / 2.0f)
	);
}

vec3 Camera::targetDirection() {
	return glm::vec3(
		cos(this->verticalOffset) * sin(this->horizontalOffset),
		0,
		cos(this->verticalOffset) * cos(this->horizontalOffset)
	);
}

void Camera::onMouseEvent(int x, int y) {
	if (this->firstPersonPerspective) {
		this->x = x;
		this->y = y;
		this->horizontalOffset += this->sensivity * .1f * float(this->width / 2 - this->x);
		this->verticalOffset += this->sensivity * .1f * float(this->height / 2 - this->y);
	}
}

void Camera::onKeyEvent(unsigned char key) {
	if (key == 'c')
		togglePerspective();
	if (this->firstPersonPerspective) 
		this->onFirstPersonControlling(key);
}



Camera::Camera(int width, int height) : width(width), height(height) {
	this->position = vec3(8, 15, -8);
	horizontalOffset = 3.14f * -0.2f;
	verticalOffset = 3.14f * -0.2f;
}

