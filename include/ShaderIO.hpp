#ifndef SHADERIO_HPP
#define SHADERIO_HPP

#include <glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct VertexOut
{
	glm::vec4 position; // clip space
	glm::vec3 world_pos;
	glm::vec2 screen_pos;
	glm::vec3 normal;
};

struct FragmentIn
{
	glm::vec3 world_pos;
	glm::vec3 normal;
};

#endif