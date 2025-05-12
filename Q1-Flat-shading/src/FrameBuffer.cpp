#include "FrameBuffer.hpp"

Framebuffer::Framebuffer(int w, int h) : width(w), height(h)
{
	color_buffer.resize(width * height, glm::vec3(0.0f));
	depth_buffer.resize(width * height, std::numeric_limits<float>::max());
}

void Framebuffer::clear_color(const glm::vec3 &color)
{
	std::fill(color_buffer.begin(), color_buffer.end(), color);
}

void Framebuffer::clear_depth()
{
	std::fill(depth_buffer.begin(), depth_buffer.end(),
			  std::numeric_limits<float>::max());
}

void Framebuffer::set_pixel(int x, int y, const glm::vec3 &color, float depth)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return; // out of bounds

	int idx = y * width + x;

	if (depth < depth_buffer[idx])
	{
		depth_buffer[idx] = depth;
		color_buffer[idx] = color;
	}
}

glm::vec3 Framebuffer::get_pixel(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return glm::vec3(0.0f); // 또는 throw?

	return color_buffer[y * width + x];
}

// [0.0, 1.0] -> [0, 255]
std::vector<unsigned char> Framebuffer::to_rgb_image() const
{
	std::vector<unsigned char> image(width * height * 3);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			const glm::vec3 color = color_buffer[y * width + x];
			int             idx   = (y * width + x) * 3;

			image[idx + 0] = static_cast<unsigned char>(
				glm::clamp(color.r, 0.0f, 1.0f) * 255);
			image[idx + 1] = static_cast<unsigned char>(
				glm::clamp(color.g, 0.0f, 1.0f) * 255);
			image[idx + 2] = static_cast<unsigned char>(
				glm::clamp(color.b, 0.0f, 1.0f) * 255);
		}
	}
	return image;
}
