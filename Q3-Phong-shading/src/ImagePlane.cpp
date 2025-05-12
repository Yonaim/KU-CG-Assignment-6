#include "ImagePlane.hpp"
#include "matrix.hpp"

void ImagePlane::setExtent(float l, float r, float t, float b)
{
	left   = l;
	right  = r;
	top    = t;
	bottom = b;
}

void ImagePlane::setDistance(float d)
{
	distance = d;
}

void ImagePlane::setDepthRange(float n, float f)
{
	z_near = n;
	z_far  = f;
}

glm::mat4 ImagePlane::getPerspectiveMatrix() const
{
	return matrix::perspective(left, right, bottom, top, z_near, z_far);
}
