#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::resizeOutput(int width, int height)
{
	this->output.resize(width * height * 3);
}

void Renderer::render(Rasterizer &rasterizer)
{
	rasterizer.framebuffer.clear_color(glm::vec3(0.0f));
	rasterizer.framebuffer.clear_depth();

	// set shaders
	rasterizer.vertex_shader->view = scene.camera.getViewMatrix();
	rasterizer.vertex_shader->projection
		= scene.camera.image_plane.getPerspectiveMatrix();

	for (const auto &object : scene.objects)
	{
		rasterizer.vertex_shader->model = object.getModelMatrix();

		for (int i = 0; i < object.mesh->n_triangles; i++)
		{
			if (!object.mesh)
				continue;
			std::array<Vertex, 3> triangle = object.mesh->get_nth_triangle(i);
			rasterizer.draw_triangle(triangle[0], triangle[1], triangle[2]);
		}
	}
}
