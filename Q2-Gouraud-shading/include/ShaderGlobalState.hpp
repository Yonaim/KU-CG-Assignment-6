#ifndef SHADER_GLOBAL_STATE_HPP
#define SHADER_GLOBAL_STATE_HPP

#include "ShaderParams.hpp"
#include "ShadingMode.hpp"

struct ShaderGlobalState
{
	const Material       *material = nullptr;
	const GlobalLighting *lighting = nullptr;
	glm::vec3             view_pos;
	ShadingMode           shading_mode;
};

#endif
