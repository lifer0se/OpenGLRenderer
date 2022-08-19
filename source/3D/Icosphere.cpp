#include "Icosphere.h"

namespace OpenGLRenderer
{
    vector<vec3> Icosphere::m_VertexList;
    vector<Icosphere::Face> Icosphere::m_FaceList;

    void Icosphere::ApplyNoiseLayers(Mesh& mesh)
    {
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        for (Vertex& vertex : mesh.Vertices)
        {
            vec3 n = normalize(vertex.Position);
            float primaryHeight = GetNoise(noise, vertex.Position, 150.0f);
            float secondaryHeight = GetNoise(noise, vertex.Position, 500.0f);
            float height = primaryHeight + secondaryHeight;
            vertex.Position += n * height * 0.05f;

            if (height > 0)
                vertex.Color = { 0.25f, 0.5f, 0.2f };
            else
                vertex.Color = { 0.1f, 0.3f, 0.2f };
        }
    }

    float Icosphere::GetNoise(FastNoiseLite noise, vec3 position, float scale)
    {
        return noise.GetNoise(position.x * scale, position.y * scale, position.z * scale);
    }

    void Icosphere::RecalculateNormals(Mesh& mesh, bool flatShaded)
    {
        if (!flatShaded)
        {
            for (int i = 0; i < (int)mesh.Vertices.size(); i++)
                mesh.Vertices[i].Normal = normalize(mesh.Vertices[i].Position);

            return;
        }

        for (int i = 0; i < (int)mesh.Indices.size() - 3; i += 3)
        {
            int a = mesh.Indices[i];
            int b = mesh.Indices[i + 1];
            int c = mesh.Indices[i + 2];

            vec3 ab = mesh.Vertices[b].Position - mesh.Vertices[a].Position;
            vec3 bc = mesh.Vertices[c].Position - mesh.Vertices[b].Position;
            vec3 ca = mesh.Vertices[a].Position - mesh.Vertices[c].Position;

            vec3 crossAB = cross(ab,bc) * -1.0f;
            vec3 crossBC = cross(bc,ca) * -1.0f;
            vec3 crossCA = cross(ca,ab) * -1.0f;

            vec3 normal = crossAB + crossBC + crossCA;
            mesh.Vertices[a].Normal += normal;
            mesh.Vertices[b].Normal += normal;
            mesh.Vertices[c].Normal += normal;
        }

        for (Vertex& vertex : mesh.Vertices)
            vertex.Normal = normalize(vertex.Normal);
    }

    Mesh Icosphere::GeneratePrimativeMesh(int LOD, bool flatShaded)
    {
        GetPrimativeIcosphere();

        map<long, int> cache;
        for (int i = 0; i < LOD; i++)
            SubdivideIcosphere(cache);

        vector<GLuint> indices;
        for (int i = 0; i < (int)m_FaceList.size(); i++)
        {
            indices.push_back(m_FaceList[i].m_IndexA);
            indices.push_back(m_FaceList[i].m_IndexC);
            indices.push_back(m_FaceList[i].m_IndexB);
        }

        vector<Vertex> vertices;
        for (int i = 0; i < (int)m_VertexList.size(); i++)
        {
            Vertex vertex {};
            vertex.Position = m_VertexList[i];
            vertex.Normal = { 0.0f, 0.0f, 0.0f };
            vertex.Color = { 0.2f, 0.2f, 0.22f };
            vertices.push_back(vertex);
        }

        Mesh mesh { vertices, indices };
        RecalculateNormals(mesh, flatShaded);
        return mesh;
    }

    void Icosphere::SubdivideIcosphere(map<long, int>& cache)
    {
        vector<Face> f;
        for (Face tri : m_FaceList)
        {
            unsigned int a = GetMiddlePoint(cache, tri.m_IndexA, tri.m_IndexB);
            unsigned int b = GetMiddlePoint(cache, tri.m_IndexB, tri.m_IndexC);
            unsigned int c = GetMiddlePoint(cache, tri.m_IndexC, tri.m_IndexA);

            f.push_back({ tri.m_IndexA, a, c });
            f.push_back({ tri.m_IndexB, b, a });
            f.push_back({ tri.m_IndexC, c, b });
            f.push_back({ a, b, c });
        }
        m_FaceList = f;
    }

    int Icosphere::GetMiddlePoint(map<long, int>& cache, int p1, int p2)
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

    void Icosphere::WriteMeshDataToFile(Mesh& mesh)
    {
        const char* filename = "icoA.txt";
        fstream file_out;
        file_out.open(filename, std::ios_base::out);
        if (!file_out.is_open()) {
            cout << "failed to open " << filename << '\n';
            return;
        }

        file_out << "        constexpr static Vertex vertices[] = {" << endl;
        for (Vertex& vertex : mesh.Vertices)
        {

            file_out << "            Vertex{ ";
            file_out << "glm::vec3(" << vertex.Position.x << "f, " << vertex.Position.y << "f, " << vertex.Position.z << "f), ";
            file_out << "glm::vec3(" << vertex.Normal.x << "f, " << vertex.Normal.y << "f, " << vertex.Normal.z << "f), ";
            file_out << "glm::vec3(" << vertex.Color.x << "f, " << vertex.Color.y << "f, " << vertex.Color.z << "f), ";
            file_out << "glm::vec2(" << vertex.Uv.x << "f, " << vertex.Uv.y << "f) }," << endl;
        }
        file_out << "        }" << endl;
        file_out << endl << "        constexpr static GLuint indices[] = {" << endl;

        int c = 0;
        file_out << endl << "            ";
        for (auto i : mesh.Indices)
        {
            if (++c % 20 == 0)
                file_out << endl << "            ";

            file_out << i << ",";
            file_out << "        };" << endl;
        }
        file_out.close();
    }

}
