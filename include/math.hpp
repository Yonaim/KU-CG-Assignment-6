#ifndef MATH_HPP
#define MATH_HPP

#include <glm/glm.hpp>
#include "math.h"

/**
 * Transformation (Rasterization) Pipeline
 *
 * 1. Modeling Transform: Position and orient objects in world coordinates
 * 2. Camera Transform: Transform from world coordinates to camera coordinate
 * 	frame
 * 3. Projection Transform: Project onto image plane
 * 4. Viewport Transform: Position image on screen
 */

#define DEGREE_TO_RADIAN(degree) (degree * (M_PI / 180))

// Model(TRS), View, Projection, viewport matrix
namespace math
{
// identity matrix
glm::mat4 identity(void)
{
	return (glm::mat4(1.0f));
}

// Translation matrix
glm::mat4 translate(const glm::vec3 &translation)
{
	glm::mat4 m(1.0f); // 단위 행렬로 시작
	m[3][0] = translation.x;
	m[3][1] = translation.y;
	m[3][2] = translation.z;
	return m;
}

// Rotation matrix (Euler angle: pitch, yaw, roll)
glm::mat4 rotate(const glm::vec3 angle)
{
	// convert degree to radian
	float pitch = DEGREE_TO_RADIAN(angle.x); // X-axis
	float yaw   = DEGREE_TO_RADIAN(angle.y); // Y-axis
	float roll  = DEGREE_TO_RADIAN(angle.z); // Z-axis

	float cx = cos(pitch);
	float sx = sin(pitch);
	float cy = cos(yaw);
	float sy = sin(yaw);
	float cz = cos(roll);
	float sz = sin(roll);

	// X axis (pitch)
	// [ 1     0      0     0 ]
	// [ 0   cosθ  -sinθ   0 ]
	// [ 0   sinθ   cosθ   0 ]
	// [ 0     0      0     1 ]
	glm::mat4 Rx(1.0f);
	Rx[1][1] = cx;
	Rx[1][2] = -sx;
	Rx[2][1] = sx;
	Rx[2][2] = cx;

	// Y axis (yaw)
	// [ cosθ   0   sinθ   0 ]
	// [   0    1     0    0 ]
	// [ -sinθ  0   cosθ   0 ]
	// [   0    0     0    1 ]
	glm::mat4 Ry(1.0f);
	Ry[0][0] = cy;
	Ry[0][2] = sy;
	Ry[2][0] = -sy;
	Ry[2][2] = cy;

	// Z axis (roll)
	// [ cosθ  -sinθ   0   0 ]
	// [ sinθ   cosθ   0   0 ]
	// [   0      0    1   0 ]
	// [   0      0    0   1 ]
	glm::mat4 Rz(1.0f);
	Rz[0][0] = cz;
	Rz[0][1] = -sz;
	Rz[1][0] = sz;
	Rz[1][1] = cz;

	// Final rotation: R = Rz * Ry * Rx
	return Rz * Ry * Rx;
}

// Scaling matrix
glm::mat4 scale(const glm::vec3 &scaling)
{
	glm::mat4 m(1.0f);
	m[0][0] = scaling.x;
	m[1][1] = scaling.y;
	m[2][2] = scaling.z;
	return m;
}

// view matrix
glm::mat4 view(const glm::vec3 &eye, const glm::vec3 &center,
			   const glm::vec3 &world_up)
{
	glm::vec3 forward = glm::normalize(center - eye);
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
	view[3][0]     = -glm::dot(right, eye);
	view[3][1]     = -glm::dot(up, eye);
	view[3][2]     = glm::dot(forward, eye);

	return view;
}

// perspective matrix
glm::mat4 perspective(float fovy, float aspect, float near, float far)
{
	float     f = 1.0f / tan(fovy / 2.0f);
	glm::mat4 m(0.0f);
	m[0][0] = f / aspect;
	m[1][1] = f;
	m[2][2] = (far + near) / (near - far);
	m[2][3] = (2 * far * near) / (near - far);
	m[3][2] = -1.0f;
	return m;
}

// viewport matrix
glm::mat4 viewport(int nx, int ny)
{
	glm::mat4 vp(1.0f);

	vp[0][0] = nx / 2.0f;
	vp[1][1] = ny / 2.0f;
	vp[3][0] = (nx - 1) / 2.0f;
	vp[3][1] = (ny - 1) / 2.0f;

	return vp;
}

} // namespace math

#endif
