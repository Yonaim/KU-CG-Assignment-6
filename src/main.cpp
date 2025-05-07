#include <iostream>
#include "gl_core.h"
#include "settings.hpp"
#include "Renderer.hpp"
#include "FragmentShaderWhite.hpp"

void        init_scene(Scene &scene);
GLFWwindow *init_glfw();
void        renderFrameLoop(Renderer &renderer, Rasterizer &rasterizer,
							GLFWwindow *window);

int main()
{
	Renderer            renderer;
	Rasterizer          rasterizer(SCR_WIDTH, SCR_HEIGHT);
	VertexShader        vs;
	FragmentShaderWhite fs;
	GLFWwindow         *window = NULL;

	// set up
	glfwSetErrorCallback(errorCallback);
	init_scene(renderer.scene);
	window = init_glfw();
	if (window == NULL)
		return (1);
	renderer.setOuput(SCR_WIDTH, SCR_HEIGHT);
	rasterizer.vertex_shader   = &vs;
	rasterizer.fragment_shader = (FragmentShader *)&fs;

	// loop
	renderFrameLoop(renderer, rasterizer, window);

	// terminate
	glfwDestroyWindow(window);
	glfwTerminate();
	return (0);
}
