#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glad/glad.h"
#include "Texture.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;
using namespace glm;

namespace OpenGLRenderer
{
	struct Vertex
	{
		vec3 postion;
		vec3 normal;
		vec3 color;
		vec2 uv;
	};

	class Mesh
	{

	public:
		vector<Vertex> Vertices;
		vector<GLuint> Indices;
		vector<Texture> Textures;

		Mesh() {};
		Mesh(vector<Vertex>& vertices, vector<GLuint>& indices);
		Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures);
	};
}

#endif
