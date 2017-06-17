#include "camera.h"
#include <iostream>


void Camera::onFirstPersonControlling(unsigned char key) {
	float momentum = .15f;
	switch (key) {
	case 'w':
		position += targetDirection() * momentum * speed;
		break;
	case 'a':
		position -= targetDirection() * momentum * speed;
		break;
	case 's':
		position -= getRight() * momentum * speed;
		break;
	case 'd':
		position += getRight() * momentum * speed;
		break;
	}
}

void Camera::togglePerspective() {
	this->firstPersonPerspective = !firstPersonPerspective;
	perspectiveChangedEvent();
}

bool Camera::isFirstPerson() {
	return this->firstPersonPerspective;
}

glm::mat4 Camera::getView() {
	vec3 up = cross(getRight(), targetDirection());
	return lookAt(
		this->position,
		this->position + getDirection(),
		up
	);
}

void Camera::perspectiveChangedEvent() {
	glutSetCursor(this->firstPersonPerspective ? GLUT_CURSOR_NONE : GLUT_CURSOR_INHERIT);
}

vec3 Camera::getDirection() {
	return glm::vec3(
		cos(this->horizontalOffset) * sin(this->horizontalOffset),
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
	this->position = vec3(0, 0, 3);
}

