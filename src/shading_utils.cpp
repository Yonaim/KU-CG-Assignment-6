#include "shading_utils.hpp"
#include "FragmentShaderFlat.hpp"

// No falloff
glm::vec3 blinn_phong(const glm::vec3 &normal, const glm::vec3 &frag_pos,
							 const glm::vec3      &view_pos,
							 const Material       &material,
							 const GlobalLighting &lighting)
{
	glm::vec3 N     = glm::normalize(normal);
	glm::vec3 V     = glm::normalize(view_pos - frag_pos);
	glm::vec3 color = glm::vec3(0.0f);

	glm::vec3 ambient = lighting.ambient_intensity * material.ka;
	color += ambient;

	for (const auto &light : lighting.lights)
	{
		glm::vec3 L = glm::normalize(light.position - frag_pos);
		glm::vec3 H = glm::normalize(L + V);

		float     diff    = glm::max(glm::dot(N, L), 0.0f);
		glm::vec3 diffuse = diff * material.kd * light.color * light.intensity;

		float spec
			= glm::pow(glm::max(glm::dot(N, H), 0.0f), material.shininess);
		glm::vec3 specular = spec * material.ks * light.color * light.intensity;

		color += diffuse + specular;
	}

	glm::vec3 color_gamma = glm::pow(color, glm::vec3(1.0f / lighting.gamma));
	return glm::clamp(color_gamma, 0.0f, 1.0f);
}

void set_flat_info(FragmentShaderFlat *fs, const VertexOut &v0,
						  const VertexOut &v1, const VertexOut &v2)
{
	if (!fs)
		return;

	glm::vec3 normal = glm::normalize(
		glm::cross(v1.world_pos - v0.world_pos, v2.world_pos - v0.world_pos));
	glm::vec3 center = (v0.world_pos + v1.world_pos + v2.world_pos) / 3.0f;
	fs->set_flat_info(normal, center);
}
