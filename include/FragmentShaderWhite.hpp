#ifndef FRAGMENTSHADERWHITE_HPP
#define FRAGMENTSHADERWHITE_HPP

#include "ShaderIO.hpp"

class FragmentShaderWhite
{
  public:
	virtual glm::vec3 fragment(const FragmentIn &in) const;
	virtual ~FragmentShaderWhite() = default;
};

glm::vec3 FragmentShaderWhite::fragment(const FragmentIn &in) const
{
	return (glm::vec3(1.0, 1.0, 1.0));
}

#endif
