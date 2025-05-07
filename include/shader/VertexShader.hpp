#ifndef VERTEXSHADER_HPP
#define VERTEXSHADER_HPP

#include "ShaderIO.hpp"

// only basic processing, so this is not a abstract class
class VertexShader
{
  public:
	// these matricies are directly modified (so not private) 
	glm::mat4 model;      // per object
	glm::mat4 view;       // per scene
	glm::mat4 projection; // per scene

	VertexOut vertex(const Vertex &in) const
	{
		VertexOut out;
		glm::vec4 world_pos = model * glm::vec4(in.position, 1.0f);
		out.world_pos       = glm::vec3(world_pos);
		out.position        = projection * view * world_pos;
		out.normal = glm::mat3(glm::transpose(glm::inverse(model))) * in.normal;
		return out;
	}
};

#endif