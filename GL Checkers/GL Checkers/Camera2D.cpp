#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>


Camera2D::Camera2D() : camPos(0, 0), camMatrix(1.0f){

}


Camera2D::~Camera2D() {

}

void Camera2D::setPos(const glm::vec2& pos) {
	camPos = pos;
	updateNeeded = true;
}


void Camera2D::setScale(float scale) {
	camScale = scale;
	updateNeeded = true;
}

void Camera2D::translate(const glm::vec2& translation) {
	camPos += (translation * -camScale);
	updateNeeded = true;
}

void Camera2D::zoom(float zoom) {
	camScale += zoom;
	updateNeeded = true;
}
void Camera2D::init(float screenWidth, float screenHeight) {
	width = screenWidth;
	height = screenHeight;
}

void Camera2D::update() {
	if (updateNeeded == true) {
		glm::mat4 orthoMatrix = glm::ortho(0.0f, width, 0.0f, height);
		camMatrix = glm::translate(orthoMatrix, glm::vec3(-camPos.x + width / 2, -camPos.y + height / 2, 0.0f));
		camMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(camScale, camScale, 0.0f)) * camMatrix;
		updateNeeded = false;
	}
}