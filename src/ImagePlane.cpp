#include "ImagePlane.hpp"
#include "math.hpp"

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
	near = n;
	far  = f;
}

glm::mat4 ImagePlane::getPerspectiveMatrix() const
{
	return math::perspective(left, right, bottom, top, near, far);
}
