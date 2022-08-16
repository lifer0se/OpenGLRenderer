#include "Icosphere.h"

namespace OpenGLRenderer
{

    Icosphere::Icosphere(int LOD, bool flatShaded)
    {
        GetPrimativeIcosphere();

        map<long, int> cache;
        for (int i = 0; i < LOD; i++)
        {
            vector<Face> f;
            for (Face tri : m_FaceList)
            {
                unsigned int a = GetMiddlePoint(m_VertexList, cache, tri.m_IndexA, tri.m_IndexB);
                unsigned int b = GetMiddlePoint(m_VertexList, cache, tri.m_IndexB, tri.m_IndexC);
                unsigned int c = GetMiddlePoint(m_VertexList, cache, tri.m_IndexC, tri.m_IndexA);

                f.push_back({ tri.m_IndexA, a, c });
                f.push_back({ tri.m_IndexB, b, a });
                f.push_back({ tri.m_IndexC, c, b });
                f.push_back({ a, b, c });
            }
            m_FaceList = f;
        }

        vector<GLuint> indices;
        for (int i = 0; i < m_FaceList.size(); i++)
        {
            indices.push_back(m_FaceList[i].m_IndexA);
            indices.push_back(m_FaceList[i].m_IndexB);
            indices.push_back(m_FaceList[i].m_IndexC);
        }

        vector<vec3> normals = CalculateNormals(indices, flatShaded);
        vector<Vertex> vertices;
        for (int i = 0; i < m_VertexList.size(); i++)
        {
            Vertex vertex {};
            vertex.Postion = m_VertexList[i];
            vertex.Normal = normals[i];
            vertex.Color = vec3 (0.2f, 0.25f, 0.3f);
            vertices.push_back(vertex);
        }

        m_Mesh = { vertices, indices };
    }

    int Icosphere::GetMiddlePoint(vector<vec3>& m_VertexList, map<long, int>& cache, int p1, int p2)
    {
        bool firstIsSmaller = p1 < p2;
        long smallerIndex = firstIsSmaller ? p1 : p2;
        long langerIndex = firstIsSmaller ? p2 : p1;
        long key = (smallerIndex << 32) + langerIndex;
        if (cache.count(key))
            return cache[key];

        float x = (m_VertexList[p1].x + m_VertexList[p2].x) / 2.0f;
        float y = (m_VertexList[p1].y + m_VertexList[p2].y) / 2.0f;
        float z = (m_VertexList[p1].z + m_VertexList[p2].z) / 2.0f;
        vec3 middlePoint { x, y, z };

        int i = m_VertexList.size();
        m_VertexList.push_back(normalize(middlePoint));
        m_VertexList.push_back(normalize(middlePoint));
        return i;
    }

    vector<vec3> Icosphere::CalculateNormals(vector<GLuint>& indices, bool flatShaded)
    {
        vector<vec3> normals;
        if (!flatShaded)
        {
            for (int i = 0; i < m_VertexList.size(); i++)
                normals.push_back(normalize(-m_VertexList[i]));

            return normals;
        }

        for (int i = 0; i < m_VertexList.size(); i++)
            normals.push_back(vec3(0.0f, 0.0f, 0.0f));

        for (int i = 0; i < indices.size() - 3; i += 3)
        {
            int a = indices[i];
            int b = indices[i + 1];
            int c = indices[i + 2];

            vec3 ab = m_VertexList[b] - m_VertexList[a];
            vec3 bc = m_VertexList[c] - m_VertexList[b];
            vec3 ca = m_VertexList[a] - m_VertexList[c];

            vec3 crossAB = cross(ab,bc) * -1.0f;
            vec3 crossBC = cross(bc,ca) * -1.0f;
            vec3 crossCA = cross(ca,ab) * -1.0f;

            vec3 normal = crossAB + crossBC + crossCA;
            normals[a] += normal;
            normals[b] += normal;
            normals[c] += normal;
        }

        for (int i = 0; i < normals.size(); i++)
            normals[i] = normalize(normals[i]);

        return normals;
    }

    void Icosphere::GetPrimativeIcosphere()
    {
        float t = (1.0f + sqrt(5.0f)) / 2.0f;

        m_VertexList.push_back(normalize(vec3 { -1.0f, t, 0.0f }));
        m_VertexList.push_back(normalize(vec3 { 1.0f, t, 0.0f }));
        m_VertexList.push_back(normalize(vec3 { -1.0f, -t, 0.0f }));
        m_VertexList.push_back(normalize(vec3 { 1.0f, -t, 0.0f }));

        m_VertexList.push_back(normalize(vec3 { 0.0f, -1.0f, t }));
        m_VertexList.push_back(normalize(vec3 { 0.0f, 1.0f, t }));
        m_VertexList.push_back(normalize(vec3 { 0.0f, -1.0f, -t }));
        m_VertexList.push_back(normalize(vec3 { 0.0f, 1.0f, -t }));

        m_VertexList.push_back(normalize(vec3 { t, 0.0f, -1.0f }));
        m_VertexList.push_back(normalize(vec3 { t, 0.0f, 1.0f }));
        m_VertexList.push_back(normalize(vec3 { -t, 0.0f, -1.0f }));
        m_VertexList.push_back(normalize(vec3 { -t, 0.0f, 1.0f }));

        // 5 m_FaceList around point 0
        m_FaceList.push_back({ 0, 11, 5 });
        m_FaceList.push_back({ 0, 5, 1 });
        m_FaceList.push_back({ 0, 1, 7 });
        m_FaceList.push_back({ 0, 7, 10 });
        m_FaceList.push_back({ 0, 10, 11 });

        // 5 adjacent m_FaceList
        m_FaceList.push_back({ 1, 5, 9 });
        m_FaceList.push_back({ 5, 11, 4 });
        m_FaceList.push_back({ 11, 10, 2 });
        m_FaceList.push_back({ 10, 7, 6 });
        m_FaceList.push_back({ 7, 1, 8 });

        // 5 m_FaceList around point 3
        m_FaceList.push_back({ 3, 9, 4 });
        m_FaceList.push_back({ 3, 4, 2 });
        m_FaceList.push_back({ 3, 2, 6 });
        m_FaceList.push_back({ 3, 6, 8 });
        m_FaceList.push_back({ 3, 8, 9 });

        // 5 adjacent m_FaceList
        m_FaceList.push_back({ 4, 9, 5 });
        m_FaceList.push_back({ 2, 4, 11 });
        m_FaceList.push_back({ 6, 2, 10 });
        m_FaceList.push_back({ 8, 6, 7 });
        m_FaceList.push_back({ 9, 8, 1 });
    }

}
