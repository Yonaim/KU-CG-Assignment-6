#ifndef VERTEXSHADER_HPP
#define VERTEXSHADER_HPP

#include <glm/glm.hpp>
#include "ShaderIO.hpp"
#include "ShaderGlobalState.hpp"
#include "ShadingMode.hpp"

class VertexShader
{
  public:
	glm::mat4 model;      // per object
	glm::mat4 view;       // per scene
	glm::mat4 projection; // per scene

	const ShaderGlobalState *global_state = nullptr;

	void set_global_state(const ShaderGlobalState *state);

	VertexOut vertex(const Vertex &in) const;
};

#endif
