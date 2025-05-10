#include "gl_core.h"
#include <GLFW/glfw3.h>
#include "Scene.hpp"
#include "settings.hpp"
#include "ShaderGlobalState.hpp"

extern int    gNumVertices;  // Number of 3D vertices.
extern int    gNumTriangles; // Number of triangles.
extern int   *gIndexBuffer;  // Vertex indices for the triangles.
extern float *gVertexBuffer;
extern float *gNormalBuffer;

void create_unit_sphere();

static void init_materials(Scene &scene)
{
	/*
	- ka = (0, 1, 0), kd = (0, 0.5, 0), ks = (0.5, 0.5, 0.5), p = 32.
	*/
	Material green_material;
	green_material.ka        = glm::vec3(0.0f, 1.0f, 0.0f); // ambient
	green_material.kd        = glm::vec3(0.0f, 0.5f, 0.0f); // diffuse
	green_material.ks        = glm::vec3(0.5f, 0.5f, 0.5f); // specular
	green_material.shininess = 32.0f;

	scene.materials["green"] = green_material;
}

static void init_lighting(Scene &scene)
{
	GlobalLighting *lighting = new GlobalLighting();

	/*
	– Use an ambient light intensity of Ia = 0.2.
	– Assume a single point light source at (−4, 4, −3), emitting white light
		with unit intensity and no falloff.
	– Apply gamma correction with γ = 2.2 in each case.
	*/
	Light point_light;
	point_light.position  = glm::vec3(-4.0f, 4.0f, -3.0f);
	point_light.color     = glm::vec3(1.0f); // white
	point_light.intensity = 1.0f;

	lighting->lights.push_back(point_light);
	lighting->ambient_intensity = 0.2f;
	lighting->gamma             = 2.2f;

	scene.lighting = lighting;
}

static void init_camera(Camera &camera)
{
	/*
	Use a camera transform with eye point at e = (0, 0, 0), and orientation
	given by u = (1, 0, 0), v = (0, 1, 0) and w = (0, 0, 1). (Note that the
	camera is looking along the direction −w.)
	*/
	camera.setEye(glm::vec3(0, 0, 0));
	camera.setDirection(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0),
						glm::vec3(0, 0, -1));
	
	/*
	Use a perspective projection transform with l = −0.1, r = 0.1, b = −0.1, t
	= 0.1, n = −0.1, f = −1000.
	*/
	camera.image_plane.setExtent(-0.1, 0.1, 0.1, -0.1);
	camera.image_plane.setDistance(0.1);
	camera.image_plane.setDepthRange(-0.1, -1000);
}

static void init_objects(Scene &scene)
{
	Mesh *unit_sphere = new Mesh();
	unit_sphere->setData(gVertexBuffer, gNormalBuffer, gNumVertices,
						 gIndexBuffer, gNumTriangles * 3);
	/*
	Use a modeling transform to transform the unit sphere to a sphere
	centered at (0, 0, −7) with a radius of 2
	*/
	Object sphere0;
	sphere0.mesh     = unit_sphere;
	sphere0.position = glm::vec3(0, 0, -7);
	sphere0.scale    = glm::vec3(2, 2, 2);

	scene.addObject(sphere0);
}

void init_scene(Scene &scene)
{
	create_unit_sphere();
	init_camera(scene.camera);
	init_materials(scene);
	init_lighting(scene);
	init_objects(scene);
	scene.objects[0].material = &scene.materials["green"];
}

GLFWwindow *init_glfw()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return (NULL);
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// ignore DPI scaling (1:1 mapping)
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

	// Create window and use
	GLFWwindow *window = glfwCreateWindow(
		SCR_WIDTH, SCR_HEIGHT, "Rasterizer (Assignment 6)", NULL, NULL);

	if (!window)
	{
		std::cout << "Window creation failed" << std::endl;
		glfwTerminate();
		return (NULL);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

#ifndef __APPLE__
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err)
				  << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return (NULL);
	}
#endif

	return (window);
}
