#include "Scene.hpp"

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::addObject(const Object &object)
{
	objects.push_back(object);
}
