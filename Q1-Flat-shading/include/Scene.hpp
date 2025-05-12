#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include "Camera.hpp"
#include "Object.hpp"

class Scene
{
  public:
	Scene();
	~Scene();

	Camera                          camera;
	std::vector<Object>             objects;
	std::map<std::string, Material> materials;
	GlobalLighting                 *lighting = nullptr;

	void addObject(const Object &object);
};

#endif
