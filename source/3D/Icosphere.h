#ifndef ICOSPHERE_CLASS_H
#define ICOSPHERE_CLASS_H

#include "Mesh.h"
#include "FastNoiseLite.h"

namespace OpenGLRenderer
{
    class Icosphere
    {
    public:

        static void ApplyNoiseLayers(Mesh& mesh);
        static void RecalculateNormals(Mesh& mesh, bool flatShaded);
        static Mesh GeneratePrimativeMesh(int LOD, bool flatShaded);

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
        static void GetPrimativeIcosphere();
        static void SubdivideIcosphere(map<long, int>& cache);
        static int GetMiddlePoint(map<long, int>& cache, int p1, int p2);

        static void WriteMeshDataToFile(Mesh& mesh);

        static float GetNoise(FastNoiseLite noise, vec3 position, float scale);

        static vector<vec3> m_VertexList;
        static vector<Face> m_FaceList;
    };
}

#endif
