#pragma once
#include "camera.h"

Camera::Camera(glm::vec2 pos, float zoom) {
	this->pos = pos;
	this->zoom = zoom;
}

Camera::Camera() {
	Camera({ 0, 0 }, 1);
}