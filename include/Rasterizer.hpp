#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include <vector>

/**
 * Vertex Transformation
 * -> Clipping & Viewport Transform
 * -> Rasterization
 * -> Shading
 */
class Rasterizer
{
  private:
	std::vector<vec4> _framebuffer;

  public:
	Rasterizer(/* args */);
	~Rasterizer();
};

Rasterizer::Rasterizer(/* args */)
{
}

Rasterizer::~Rasterizer()
{
}

#endif
