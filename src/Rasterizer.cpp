#include "Rasterizer.hpp"

Rasterizer::Rasterizer(int w, int h) : frameBuffer(w, h)
{
}

// Returns signed area (used for inside-triangle test)
static float edge_test(const glm::vec2 &a, const glm::vec2 &b,
					   const glm::vec2 &c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

// Converts NDC [-1, 1] to screen space [0~width, 0~height]
static glm::vec2 ndc_to_screen(const glm::vec4 &p, int width, int height)
{
	return glm::vec2((p.x * 0.5f + 0.5f) * width, (p.y * 0.5f + 0.5f) * height);
}

void Rasterizer::transform_vertices(const Vertex &v0, const Vertex &v1,
									const Vertex &v2, VertexOut &out0,
									VertexOut &out1, VertexOut &out2)
{
	// local -> world -> view -> clip
	out0 = vertex_shader->vertex(v0);
	out1 = vertex_shader->vertex(v1);
	out2 = vertex_shader->vertex(v2);

	// clip -> NDC
	out0.position = out0.position / out0.position.w;
	out1.position = out1.position / out1.position.w;
	out2.position = out2.position / out2.position.w;

	// NDC -> screen
	out0.screen_pos = ndc_to_screen(out0.position);
	out1.screen_pos = ndc_to_screen(out1.position);
	out2.screen_pos = ndc_to_screen(out2.position);
}

void Rasterizer::rasterize_triangle(const VertexOut &v0, const VertexOut &v1,
									const VertexOut &v2)
{
	float area = edge_test(v0.screen_pos, v1.screen_pos, v2.screen_pos);
	if (area == 0.0f)
		return;

	for (int y = 0; y < framebuffer.height; ++y)
	{
		for (int x = 0; x < framebuffer.width; ++x)
		{
			glm::vec2 p(x + 0.5f, y + 0.5f);

			float w0 = edge_test(v1.screen_pos, v2.screen_pos, p);
			float w1 = edge_test(v2.screen_pos, v0.screen_pos, p);
			float w2 = edge_test(v0.screen_pos, v1.screen_pos, p);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 /= area;

				float depth = w0 * v0.position.z + w1 * v1.position.z
							  + w2 * v2.position.z;
				int index = y * framebuffer.width + x;

				if (depth < framebuffer.depth_buffer[index])
				{
					framebuffer.depth_buffer[index] = depth;

					FragmentIn frag;
					frag.world_pos = w0 * v0.world_pos + w1 * v1.world_pos
									 + w2 * v2.world_pos;
					frag.normal = glm::normalize(w0 * v0.normal + w1 * v1.normal
												 + w2 * v2.normal);

					glm::vec3 color = fragment_shader->fragment(frag);
					framebuffer.color_buffer[index] = color;
				}
			}
		}
	}
}

void Rasterizer::draw_triangle(const Vertex &v0, const Vertex &v1,
							   const Vertex &v2)
{
	VertexOut out0, out1, out2;

	transform_vertices(v0, v1, v2, out0, out1, out2);
	rasterize_triangle(out0, out1, out2);
}
