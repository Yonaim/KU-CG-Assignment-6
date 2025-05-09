#include "ShadingMode.hpp"
#include "FragmentShaderFlat.hpp"
#include "FragmentShaderGouraud.hpp"
#include "FragmentShaderPhong.hpp"

FragmentShader *make_fragment_shader(ShadingMode mode)
{
	switch (mode)
	{
	case ShadingMode::Flat:
		return new FragmentShaderFlat(glm::vec3(0), glm::vec3(0));
	case ShadingMode::Gouraud:
		return new FragmentShaderGouraud();
	case ShadingMode::Phong:
		return new FragmentShaderPhong();
	default:
		throw std::runtime_error("Unknown shading mode.");
	}
}
