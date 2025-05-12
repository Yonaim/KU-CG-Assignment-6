#ifndef SHADINGUTILS_HPP
#define SHADINGUTILS_HPP

#include <glm/glm.hpp>
#include "ShaderParams.hpp"
#include "ShaderIO.hpp"

class FragmentShaderFlat;

glm::vec3 blinn_phong(const glm::vec3 &normal, const glm::vec3 &frag_pos,
					  const glm::vec3 &view_pos, const Material &material,
					  const GlobalLighting &lighting);

#endif
