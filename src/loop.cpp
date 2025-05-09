#include "gl_core.h"
#include "Renderer.hpp"
#include "Rasterizer.hpp"
#include "settings.hpp"

static void flipImageVertically(std::vector<unsigned char> &image, int width,
								int height)
{
	int                        rowSize = width * 3; // RGB
	std::vector<unsigned char> temp(rowSize);

	for (int y = 0; y < height / 2; ++y)
	{
		int topIndex    = y * rowSize;
		int bottomIndex = (height - 1 - y) * rowSize;

		std::memcpy(temp.data(), &image[topIndex], rowSize);
		std::memcpy(&image[topIndex], &image[bottomIndex], rowSize);
		std::memcpy(&image[bottomIndex], temp.data(), rowSize);
	}
}

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
			flipImageVertically(renderer.output, SCR_WIDTH, SCR_HEIGHT);

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
