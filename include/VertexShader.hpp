#ifndef VERTEXSHADER_HPP
#define VERTEXSHADER_HPP

#include "ShaderIO.hpp"
#include "ShaderGlobalState.hpp"
#include "shading_utils.hpp"

class VertexShader
{
  public:
	glm::mat4 model;      // per object
	glm::mat4 view;       // per scene
	glm::mat4 projection; // per scene

	const ShaderGlobalState *global_state = nullptr;

	void set_global_state(const ShaderGlobalState *state)
	{
		global_state = state;
	}

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