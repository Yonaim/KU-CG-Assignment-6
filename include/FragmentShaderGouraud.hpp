#ifndef FRAGMENTSHADERGOURAUD_HPP
#define FRAGMENTSHADERGOURAUD_HPP

#include "FragmentShader.hpp"

class FragmentShaderGouraud : public FragmentShader
{
  public:
	// Return color that already calculated in vertex shader
	glm::vec3 fragment(const FragmentIn &in) const override
	{
		return in.color;
	}
};

#endif
