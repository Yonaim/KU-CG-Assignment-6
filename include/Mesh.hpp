#ifndef MESH_HPP
#define MESH_HPP

#include "ShaderIO.hpp"

class Mesh
{
  public:
	float *vertexBuffer = nullptr; // vertex: 3 floats per vertex
	int   *indexBuffer  = nullptr; // indices: 3 per triangle
	int    n_vertices;
	int    n_indices;
	int    n_triangles;

	Mesh() = default;

	~Mesh()
	{
		delete[] vertexBuffer;
		delete[] indexBuffer;
	}

	void setData(float *vertices, int numVertices, int *indices, int numIndices)
	{
		vertexBuffer = vertices;
		indexBuffer  = indices;
		n_vertices   = numVertices;
		n_indices    = numIndices;
	}
	std::array<Vertex, 3> get_nth_triangle(int idx) const;
};

std::array<Vertex, 3> Mesh::get_nth_triangle(int idx) const
{
	std::array<Vertex, 3> triangle;

	int i0 = indexBuffer[idx * 3 + 0];
	int i1 = indexBuffer[idx * 3 + 1];
	int i2 = indexBuffer[idx * 3 + 2];

	const glm::vec3 v0(vertexBuffer[3 * i0 + 0], vertexBuffer[3 * i0 + 1],
					   vertexBuffer[3 * i0 + 2]);

	const glm::vec3 v1(vertexBuffer[3 * i1 + 0], vertexBuffer[3 * i1 + 1],
					   vertexBuffer[3 * i1 + 2]);

	const glm::vec3 v2(vertexBuffer[3 * i2 + 0], vertexBuffer[3 * i2 + 1],
					   vertexBuffer[3 * i2 + 2]);

	triangle[0].position = v0;
	triangle[1].position = v1;
	triangle[2].position = v2;

	// temporary
	for (int i = 0; i < 3; ++i)
		triangle[i].normal = glm::vec3(0.0f, 0.0f, 1.0f);

	return triangle;
}

#endif
