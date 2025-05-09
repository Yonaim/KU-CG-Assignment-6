#ifndef SHADER_PARAMS_HPP
#define SHADER_PARAMS_HPP

#include <glm/glm.hpp>

struct Material
{
	glm::vec3 ka; // ambient
	glm::vec3 kd; // diffuse
	glm::vec3 ks; // specular
	float     shininess;
};

struct Light
{
	glm::vec3 position;
	glm::vec3 color;
	float     intensity;
};

struct GlobalLighting
{
	Light light;
	float ambient_intensity;
	float gamma;
};

#endif
