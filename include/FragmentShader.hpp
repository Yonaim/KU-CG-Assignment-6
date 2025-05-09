#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include "ShaderIO.hpp"
#include "ShaderGlobalState.hpp"

// Abstract class
class FragmentShader
{
  protected:
	const ShaderGlobalState *global_state = nullptr;

  public:
	virtual glm::vec3 fragment(const FragmentIn &in) const = 0;
	virtual ~FragmentShader()                              = default;

	virtual void set_global_state(const ShaderGlobalState *state)
	{
		global_state = state;
	}
};

#endif
