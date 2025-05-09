#include "Mesh.hpp"

Mesh::Mesh() = default;

Mesh::~Mesh()
{
	delete[] vertexBuffer;
	delete[] indexBuffer;
}

void Mesh::setData(float *vertices, float *normals, int numVertices,
				   int *indices, int numIndices)
{
	this->vertexBuffer = vertices;
	this->normalBuffer = normals;
	this->n_vertices   = numVertices;
	this->indexBuffer  = indices;
	this->n_indices    = numIndices;
	this->n_triangles  = numIndices / 3;
}

std::array<Vertex, 3> Mesh::get_nth_triangle(int idx) const
{
	std::array<Vertex, 3> triangle;

	int i0 = indexBuffer[idx * 3 + 0];
	int i1 = indexBuffer[idx * 3 + 1];
	int i2 = indexBuffer[idx * 3 + 2];

	glm::vec3 v0(vertexBuffer[3 * i0 + 0], vertexBuffer[3 * i0 + 1],
				 vertexBuffer[3 * i0 + 2]);
	glm::vec3 v1(vertexBuffer[3 * i1 + 0], vertexBuffer[3 * i1 + 1],
				 vertexBuffer[3 * i1 + 2]);
	glm::vec3 v2(vertexBuffer[3 * i2 + 0], vertexBuffer[3 * i2 + 1],
				 vertexBuffer[3 * i2 + 2]);

	triangle[0].position = v0;
	triangle[1].position = v1;
	triangle[2].position = v2;

	// temporary
	for (int i = 0; i < 3; ++i)
		triangle[i].normal = glm::vec3(0.0f, 0.0f, 1.0f);

	return triangle;
}
