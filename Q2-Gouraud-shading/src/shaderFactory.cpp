#include <stdlib.h>
#include "ShadingMode.hpp"
#include "FragmentShaderFlat.hpp"
#include "FragmentShaderGouraud.hpp"
#include "FragmentShaderPhong.hpp"

FragmentShader *make_fragment_shader(ShadingMode mode)
{
	switch (mode)
	{
	case ShadingMode::Flat:
		return new FragmentShaderFlat();
	case ShadingMode::Gouraud:
		return new FragmentShaderGouraud();
	case ShadingMode::Phong:
		return new FragmentShaderPhong();
	default:
		exit(1); // Unknown shading mode
	}
}
