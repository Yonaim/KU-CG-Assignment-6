#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <iostream>
#include "ImagePlane.hpp"

class Camera
{
  private:
	glm::vec3  eye;     // position of camera
	glm::vec3  right;   // u
	glm::vec3  up;      // v
	glm::vec3  forward; // w
	
	public:
	ImagePlane image_plane;
	
	Camera();
	~Camera();
	void      setEye(glm::vec3 eye);
	void      setDirection(glm::vec3 right, glm::vec3 up, glm::vec3 forward);
	glm::vec3 getEye() const;
	glm::vec3 getRight() const;
	glm::vec3 getUp() const;
	glm::vec3 getForward() const;
	glm::mat4 getViewMatrix() const;
};

#endif
