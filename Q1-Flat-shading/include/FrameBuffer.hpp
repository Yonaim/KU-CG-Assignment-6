#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <glm/glm.hpp>
#include <vector>

class Framebuffer
{
  public:
	int                    width, height;
	std::vector<glm::vec3> color_buffer;
	std::vector<float>     depth_buffer;

	Framebuffer(int w, int h);
	void clear_color(const glm::vec3 &color);
	void clear_depth();

	void      set_pixel(int x, int y, const glm::vec3 &color, float depth);
	glm::vec3 get_pixel(int x, int y) const;
	std::vector<unsigned char> to_rgb_image() const;
};

#endif
