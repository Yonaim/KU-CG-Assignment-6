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

std::array<Vertex, 3> Mesh::get_nth_triangle(int n) const
{
	std::array<Vertex, 3> triangle;

	int x_idx = indexBuffer[n * 3 + 0];
	int y_idx = indexBuffer[n * 3 + 1];
	int z_idx = indexBuffer[n * 3 + 2];

	glm::vec3 x_v(vertexBuffer[3 * x_idx + 0], vertexBuffer[3 * x_idx + 1],
				  vertexBuffer[3 * x_idx + 2]);
	glm::vec3 y_v(vertexBuffer[3 * y_idx + 0], vertexBuffer[3 * y_idx + 1],
				  vertexBuffer[3 * y_idx + 2]);
	glm::vec3 z_v(vertexBuffer[3 * z_idx + 0], vertexBuffer[3 * z_idx + 1],
				  vertexBuffer[3 * z_idx + 2]);

	glm::vec3 x_n(normalBuffer[3 * x_idx + 0], normalBuffer[3 * x_idx + 1],
				  normalBuffer[3 * x_idx + 2]);
	glm::vec3 y_n(normalBuffer[3 * y_idx + 0], normalBuffer[3 * y_idx + 1],
				  normalBuffer[3 * y_idx + 2]);
	glm::vec3 z_n(normalBuffer[3 * z_idx + 0], normalBuffer[3 * z_idx + 1],
				  normalBuffer[3 * z_idx + 2]);

	triangle[0].position = x_v;
	triangle[1].position = y_v;
	triangle[2].position = z_v;
	triangle[0].normal   = x_n;
	triangle[1].normal   = y_n;
	triangle[2].normal   = z_n;

	return triangle;
}
