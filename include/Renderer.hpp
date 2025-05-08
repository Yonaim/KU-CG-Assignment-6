#ifndef RENDERER_HPP
#define RENDERER_HPP

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#endif

#include "Rasterizer.hpp"
#include "Scene.hpp"

class Renderer
{
  private:
  public:
	Scene                      scene;
	std::vector<unsigned char> output;

	Renderer();
	~Renderer();
	void resizeOutput(int width, int height);
	void render(Rasterizer &rasterizer);
};

#endif
