#ifndef ICOSPHERE_CLASS_H
#define ICOSPHERE_CLASS_H

#include "Mesh.h"

namespace OpenGLRenderer
{
    class Icosphere
    {
    public:

        Icosphere(int LOD, bool flatShaded);
        ~Icosphere() {};

        inline Mesh GetMesh() { return m_Mesh; };

    private:

        struct Face
        {
            unsigned int m_IndexA;
            unsigned int m_IndexB;
            unsigned int m_IndexC;

            Face(unsigned int a, unsigned int b, unsigned int c)
                : m_IndexA(a), m_IndexB(b), m_IndexC(c)
            {
            }
        };
        void GetPrimativeIcosphere();
        int GetMiddlePoint(vector<vec3>& vertexList, map<long, int>& cache, int p1, int p2);
        vector<vec3> CalculateNormals(vector<GLuint>& indices, bool flatShaded);

        vector<vec3> m_VertexList;
        vector<Face> m_FaceList;
        Mesh m_Mesh;
    };
}

#endif
