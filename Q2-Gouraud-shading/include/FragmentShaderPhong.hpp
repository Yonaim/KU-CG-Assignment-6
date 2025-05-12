#ifndef FRAGMENTSHADERPHONG_HPP
#define FRAGMENTSHADERPHONG_HPP

#include "FragmentShader.hpp"
#include "shading_utils.hpp"

class FragmentShaderPhong : public FragmentShader
{
  public:
	glm::vec3 fragment(const FragmentIn &in) const override
	{
		return blinn_phong(glm::normalize(in.normal), in.position,
						   global_state->view_pos, *global_state->material,
						   *global_state->lighting);
	}
};

#endif
