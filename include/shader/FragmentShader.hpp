#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include "ShaderIO.hpp"

// Abstract class
// because I later add multiple fragment shaders
class FragmentShader
{
  public:
	virtual glm::vec3 fragment(const FragmentIn &in) const = 0;
	virtual ~FragmentShader()                              = default;
};

#endif
