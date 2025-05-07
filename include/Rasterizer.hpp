#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include <vector>
#include <glm/glm.hpp>
#include "FrameBuffer.hpp"
#include "VertexShader.hpp"
#include "FragmentShader.hpp"

/**
 * Vertex Transformation
 * -> Clipping & Viewport Transform
 * -> Rasterization
 * -> Shading
 */
class Rasterizer
{
  public:
	Framebuffer     framebuffer;
	VertexShader   *vertex_shader   = NULL;
	FragmentShader *fragment_shader = NULL;

	Rasterizer(int w, int h);

	void draw_triangle(const Vertex &v0, const Vertex &v1, const Vertex &v2);

  private:
	void rasterize_triangle(const VertexOut &v0, const VertexOut &v1,
							const VertexOut &v2);
	void transform_vertices(const Vertex &v0, const Vertex &v1,
							const Vertex &v2, VertexOut &out0, VertexOut &out1,
							VertexOut &out2);
};

#endif
