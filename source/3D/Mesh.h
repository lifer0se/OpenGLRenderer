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
		vec3 Postion;
		vec3 Normal;
		vec3 Color;
		vec2 Uv;
    };

	class Mesh
	{

	public:
		vector<Vertex> Vertices;
		vector<GLuint> Indices;

		Mesh() {};
		Mesh(vector<Vertex>& vertices, vector<GLuint>& indices);
	};
}

#endif
