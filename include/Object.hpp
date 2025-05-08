#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "matrix.hpp"

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
		glm::mat4 t = matrix::translate(position);
		glm::mat4 r = matrix::rotate(rotation);
		glm::mat4 s = matrix::scale(scale);

		return t * r * s;
	}
};

#endif
