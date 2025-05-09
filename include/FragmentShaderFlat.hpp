#ifndef FRAGMENTSHADERFLAT_HPP
#define FRAGMENTSHADERFLAT_HPP

#include "FragmentShader.hpp"
#include "shading_utils.hpp"

class FragmentShaderFlat : public FragmentShader
{
	glm::vec3         flat_normal;
	glm::vec3         flat_position;
	mutable glm::vec3 cached_color; // if dirty is false, return this
	mutable bool      dirty = true; // recompute when dirty bit = true

  public:
	FragmentShaderFlat() = default;

	FragmentShaderFlat(const glm::vec3 &normal, const glm::vec3 &position)
		: flat_normal(normal), flat_position(position)
	{
	}

	void set_flat_info(const glm::vec3 &normal, const glm::vec3 &position)
	{
		flat_normal   = normal;
		flat_position = position;
		dirty         = true;
	}

	void set_global_state(const ShaderGlobalState *state) override
	{
		FragmentShader::set_global_state(state);
		dirty = true;
	}

	glm::vec3 fragment(const FragmentIn &) const override
	{
		if (dirty)
		{
			cached_color = blinn_phong(
				flat_normal, flat_position, global_state->view_pos,
				*global_state->material, *global_state->lighting);
			dirty = false;
		}
		return cached_color;
	}
};

#endif
