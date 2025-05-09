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

	// view and projection matrix are per scene
	rasterizer.vertex_shader->view = scene.camera.getViewMatrix();
	rasterizer.vertex_shader->projection
		= scene.camera.image_plane.getPerspectiveMatrix();

	for (const auto &obj : scene.objects)
	{
		global_state.material = obj.material;
		setGlobalStateToShaders(rasterizer);

		if (rasterizer.vertex_shader)
			rasterizer.vertex_shader->model = obj.getModelMatrix();

		for (int i = 0; i < obj.mesh->n_triangles; i++)
		{
			if (!obj.mesh)
				continue;
			std::array<Vertex, 3> triangle = obj.mesh->get_nth_triangle(i);
			rasterizer.draw_triangle(global_state, triangle[0], triangle[1],
									 triangle[2]);
		}
	}
}

void Renderer::setMaterial(const Material *mat)
{
	global_state.material = mat;
}

void Renderer::setLighting(const GlobalLighting *light)
{
	global_state.lighting = light;
}

void Renderer::setViewPosition(const glm::vec3 &view_pos)
{
	global_state.view_pos = view_pos;
}

void Renderer::setShadingMode(ShadingMode mode)
{
	global_state.shading_mode = mode;
}

void Renderer::setGlobalStateToShaders(Rasterizer &rasterizer)
{
	if (rasterizer.vertex_shader)
		rasterizer.vertex_shader->set_global_state(&global_state);
	if (rasterizer.fragment_shader)
		rasterizer.fragment_shader->set_global_state(&global_state);
}
