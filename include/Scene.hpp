#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "Camera.hpp"
#include "Object.hpp"

class Scene
{
  public:
	Scene();
	~Scene();

	Camera              camera;
	std::vector<Object> objects;

	void addObject(const Object &object);
};

#endif
