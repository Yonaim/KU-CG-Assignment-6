#ifndef IMAGEPLANE_HPP
#define IMAGEPLANE_HPP

#include <glm/glm.hpp>

class ImagePlane
{
  public:
	float left, right;
	float top, bottom;
	float distance;
	float z_near, z_far;

	ImagePlane()  = default;
	~ImagePlane() = default;

	void setExtent(float l, float r, float t, float b); // l, r, t, b
	void setDistance(float d);                          // distance
	void setDepthRange(float n, float f);               // near, far

	glm::mat4 getPerspectiveMatrix() const;
};

#endif
