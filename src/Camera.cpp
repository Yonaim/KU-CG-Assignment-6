#include "Camera.hpp"
#include "matrix.hpp"

Camera::Camera()
	: eye(0.0f), right(1.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
	  forward(0.0f, 0.0f, 1.0f)
{
}

Camera::~Camera() = default;

void Camera::setEye(glm::vec3 e)
{
	eye = e;
}

void Camera::setDirection(glm::vec3 r, glm::vec3 u, glm::vec3 f)
{
	right   = glm::normalize(r);
	up      = glm::normalize(u);
	forward = glm::normalize(f);
}

glm::vec3 Camera::getEye() const
{
	return eye;
}

glm::vec3 Camera::getRight() const
{
	return right;
}

glm::vec3 Camera::getUp() const
{
	return up;
}

glm::vec3 Camera::getForward() const
{
	return forward;
}

glm::mat4 Camera::getViewMatrix() const
{
	glm::vec3 lookat = eye + forward;
	return (matrix::view(eye, lookat, up));
}