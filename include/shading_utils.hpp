#ifndef SHADINGUTILS_HPP
#define SHADINGUTILS_HPP

#include <glm/glm.hpp>
#include "ShaderParams.hpp"

// no falloff
// inline function
inline glm::vec3 blinn_phong(
	const glm::vec3& normal,
	const glm::vec3& frag_pos,
	const glm::vec3& view_pos,
	const Material& material,
	const GlobalLighting& lighting)
{
	glm::vec3 N = glm::normalize(normal);
	glm::vec3 L = glm::normalize(lighting.light.position - frag_pos);
	glm::vec3 V = glm::normalize(view_pos - frag_pos);
	glm::vec3 H = glm::normalize(L + V);

	glm::vec3 ambient = lighting.ambient_intensity * material.ka;
	float diff = glm::max(glm::dot(N, L), 0.0f);
	glm::vec3 diffuse = diff * material.kd;
	float spec = glm::pow(glm::max(glm::dot(N, H), 0.0f), material.shininess);
	glm::vec3 specular = spec * material.ks;

	glm::vec3 color_linear = ambient + diffuse + specular;
	glm::vec3 color_gamma = glm::pow(color_linear, glm::vec3(1.0f / lighting.gamma));
	return glm::clamp(color_gamma, 0.0f, 1.0f);
}

#endif
