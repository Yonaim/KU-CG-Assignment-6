#include <iostream>
#include "gl_core.h"
#include "settings.hpp"
#include "Renderer.hpp"
#include "VertexShader.hpp"
#include "ShadingMode.hpp"

void            init_scene(Scene &scene);
GLFWwindow     *init_glfw();
void            renderFrameLoop(Renderer &renderer, Rasterizer &rasterizer,
								GLFWwindow *window);
FragmentShader *make_fragment_shader(ShadingMode mode);

// if you want change shading mode, change the value of 'mode'
int main()
{
	Renderer        renderer;
	Rasterizer      rasterizer(SCR_WIDTH, SCR_HEIGHT);
	GLFWwindow     *window       = NULL;
	ShadingMode     shading_mode = ShadingMode::Gouraud; // shading mode
	VertexShader    vs;
	FragmentShader *fs = make_fragment_shader(shading_mode);

	// set up
	glfwSetErrorCallback(errorCallback);
	init_scene(renderer.scene);
	window = init_glfw();
	if (window == NULL)
		return (1);
	renderer.setShadingMode(shading_mode);
	renderer.resizeOutput(SCR_WIDTH, SCR_HEIGHT);
	rasterizer.vertex_shader   = &vs;
	rasterizer.fragment_shader = fs;

	// loop
	renderFrameLoop(renderer, rasterizer, window);

	// terminate
	glfwDestroyWindow(window);
	glfwTerminate();
	delete fs;

	return (0);
}
