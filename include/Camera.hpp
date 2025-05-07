#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <iostream>

class Camera
{
  private:
	glm::vec3 eye;      // position of camera
	glm::vec3 right;    // u
	glm::vec3 up;       // v
	glm::vec3 forward;  // w
	float     distance; // distance from image plane (aka. focal length)

  public:
	Camera();
	~Camera();
	void setEye(glm::vec3 eye);
	void setDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward);
	void setDistance(float distance);
};

#endif
