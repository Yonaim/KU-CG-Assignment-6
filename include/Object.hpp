#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "math.hpp"

class Object
{
  public:
	Mesh     *mesh;
	glm::vec3 position;
	glm::vec3 rotation; // Euler angles
	glm::vec3 scale;

	Object() = default;

	glm::mat4 getModelMatrix() const
	{
		glm::mat4 t = math::translate(position);
		glm::mat4 r = math::rotate(rotation);
		glm::mat4 s = math::scale(scale);

		return t * r * s;
	}
};

#endif
