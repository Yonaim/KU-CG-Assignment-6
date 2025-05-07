#ifndef MESH_HPP
#define MESH_HPP

#include <array>
#include "ShaderIO.hpp"

class Mesh
{
  public:
	float *vertexBuffer = nullptr; // vertex: 3 floats per vertex
	int   *indexBuffer  = nullptr; // indices: 3 per triangle
	int    n_vertices   = 0;
	int    n_indices    = 0;
	int    n_triangles  = 0;

	Mesh();
	~Mesh();

	void setData(float *vertices, int numVertices, int *indices,
				 int numIndices);
	std::array<Vertex, 3> get_nth_triangle(int idx) const;
};

#endif
