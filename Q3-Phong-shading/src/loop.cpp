#include "gl_core.h"
#include "Renderer.hpp"
#include "Rasterizer.hpp"
#include "settings.hpp"


static void updateGlobalState(Renderer &renderer, const glm::vec3 &camera_pos,
							  const GlobalLighting *lighting)
{
	renderer.setViewPosition(camera_pos);
	renderer.setLighting(lighting);
}

void renderFrameLoop(Renderer &renderer, Rasterizer &rasterizer,
					 GLFWwindow *window)
{
	bool needRecompute = true;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(SCR_WIDTH, SCR_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE,
					 &renderer.output[0]);

		if (needRecompute)
		{
			updateGlobalState(renderer, renderer.scene.camera.getEye(),
							  renderer.scene.lighting);
							  
			std::cout << "Starting rasterization..." << std::endl;

			renderer.render(rasterizer);
			renderer.output = rasterizer.framebuffer.to_rgb_image();

			std::cout << "Rasterization complete!" << std::endl;
			needRecompute = false;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
			|| glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
