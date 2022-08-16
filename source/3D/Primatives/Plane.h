#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include "Mesh.h"

namespace OpenGLRenderer
{
    class Plane
    {

    public:

        static Mesh Make() {
            vector<Vertex> verts { vertices, vertices + sizeof(vertices) / sizeof(Vertex) };
            vector<GLuint> ind { indices, indices + sizeof(indices) / sizeof(GLuint) };
            return { verts, ind };
        };

    private:
        constexpr static Vertex vertices[] =
        { //               COORDINATES          /            NORMALS          /           COLORS         /       TexCoord        //
            Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.25f, 0.3f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.25f, 0.3f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.25f, 0.3f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.2f, 0.25f, 0.3f), glm::vec2(1.0f, 0.0f)}
        };

        constexpr static GLuint indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };
    };
}

#endif
