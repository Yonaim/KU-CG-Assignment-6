#define _USE_MATH_DEFINES
#include "matrix.hpp"
#include <cmath>

namespace matrix
{

glm::mat4 identity(void)
{
	return glm::mat4(1.0f);
}

glm::mat4 translate(const glm::vec3 &translation)
{
	glm::mat4 m(1.0f);
	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;
	return m;
}

glm::mat4 rotate(const glm::vec3 angle)
{
	float pitch = DEGREE_TO_RADIAN(angle.x);
	float yaw   = DEGREE_TO_RADIAN(angle.y);
	float roll  = DEGREE_TO_RADIAN(angle.z);

	float cx = cos(pitch);
	float sx = sin(pitch);
	float cy = cos(yaw);
	float sy = sin(yaw);
	float cz = cos(roll);
	float sz = sin(roll);

	glm::mat4 Rx(1.0f);
	Rx[1][1] = cx;
	Rx[1][2] = -sx;
	Rx[2][1] = sx;
	Rx[2][2] = cx;

	glm::mat4 Ry(1.0f);
	Ry[0][0] = cy;
	Ry[0][2] = sy;
	Ry[2][0] = -sy;
	Ry[2][2] = cy;

	glm::mat4 Rz(1.0f);
	Rz[0][0] = cz;
	Rz[0][1] = -sz;
	Rz[1][0] = sz;
	Rz[1][1] = cz;

	return Rz * Ry * Rx;
}

glm::mat4 scale(const glm::vec3 &scaling)
{
	glm::mat4 m(1.0f);
	m[0][0] = scaling.x;
	m[1][1] = scaling.y;
	m[2][2] = scaling.z;
	return m;
}

glm::mat4 view(const glm::vec3 &eye, const glm::vec3 &lookat,
			   const glm::vec3 &world_up)
{
	glm::vec3 forward = glm::normalize(lookat - eye);
	glm::vec3 right   = glm::normalize(glm::cross(world_up, forward));
	glm::vec3 up      = glm::cross(forward, right);

	glm::mat4 view = glm::mat4(1.0f);
	view[0][0]     = right.x;
	view[0][1]     = right.y;
	view[0][2]     = right.z;
	view[1][0]     = up.x;
	view[1][1]     = up.y;
	view[1][2]     = up.z;
	view[2][0]     = -forward.x;
	view[2][1]     = -forward.y;
	view[2][2]     = -forward.z;
	view[3][0]     = glm::dot(right, eye);
	view[3][1]     = glm::dot(up, eye);
	view[3][2]     = -glm::dot(forward, eye);

	return view;
}

glm::mat4 perspective(float l, float r, float b, float t, float n, float f)
{
	glm::mat4 m(0.0f);

	m[0][0] = 2.0f * n / (r - l);
	m[1][1] = 2.0f * n / (t - b);
	m[2][2] = (f + n) / (n - f);
	m[2][3] = 1.0f; // perspective divide
	m[3][2] = 2.0f * f * n / (f - n);
	m[2][0] = (l + r) / (l - r);
	m[2][1] = (b + t) / (b - t);

	return m;
}

glm::mat4 viewport(int nx, int ny)
{
	glm::mat4 vp(1.0f);
	vp[0][0] = nx / 2.0f;
	vp[1][1] = ny / 2.0f;
	vp[3][0] = (nx - 1) / 2.0f;
	vp[3][1] = (ny - 1) / 2.0f;
	return vp;
}

} // namespace matrix
