#include "Mesh.h"

namespace OpenGLRenderer
{
    Mesh::Mesh(vector<Vertex> &vertices, vector<GLuint> &indices)
	{
		Mesh::Vertices = vertices;
		Mesh::Indices = indices;
	}

	Mesh::Mesh(vector<Vertex> &vertices, vector<GLuint> &indices, vector<Texture> &textures)
	{
		Mesh::Vertices = vertices;
		Mesh::Indices = indices;
		Mesh::Textures = textures;
	}
}
