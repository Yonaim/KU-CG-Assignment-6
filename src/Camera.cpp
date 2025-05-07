#include "Camera.hpp"

Camera::Camera()
	: eye(0.0f), right(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
	  forward(0.0f, 0.0f, 1.0f), distance(1.0f)
{
}

Camera::~Camera() = default;

void Camera::setEye(glm::vec3 e)
{
	eye = e;
}

void Camera::setDirection(glm::vec3 u, glm::vec3 v, glm::vec3 w)
{
	right   = glm::normalize(u); // u
	up      = glm::normalize(v); // v
	forward = glm::normalize(w); // w
}

void Camera::setDistance(float d)
{
	if (d <= 0.0f)
		std::cerr << "[Camera] Invalid distance: " << d << std::endl;
	else
		distance = d;
}
