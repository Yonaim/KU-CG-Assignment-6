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
#include "ShaderGlobalState.hpp"

class Renderer
{
  private:
  public:
	Scene                      scene;
	std::vector<unsigned char> output;
	ShaderGlobalState          global_state;

	Renderer();
	~Renderer();
	void resizeOutput(int width, int height);
	void render(Rasterizer &rasterizer);

	// Global state
	void setGlobalStateToShaders(Rasterizer &rasterizer);
	void setMaterial(const Material *mat);
	void setLighting(const GlobalLighting *light);
	void setViewPosition(const glm::vec3 &view_pos);
	void setShadingMode(ShadingMode mode);
};

#endif
