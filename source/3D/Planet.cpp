#include "Planet.h"
#include "Icosphere.h"
#include "Primatives/Icosphere_LOD5.h"

namespace OpenGLRenderer
{
    Planet::Planet(std::shared_ptr<Shader> planetShader, std::shared_ptr<Shader> seaShader)
    {
        SetName("Planet1");

        Mesh ico = IcospherePrimative::Make();
        Icosphere::ApplyNoiseLayers(ico);
        Icosphere::RecalculateNormals(ico, true);
        m_MeshRenderer = std::make_shared<MeshRenderer>(planetShader, ico, "Ico1");
        Actor::AddChild(m_MeshRenderer);

        Mesh sea = IcospherePrimative::Make();
        for (Vertex& v : sea.Vertices)
            v.Color = vec3 { 0.1f, 0.2f, 0.95f };

        m_MeshRenderer = std::make_shared<MeshRenderer>(seaShader, sea, "Sea1");
        m_MeshRenderer->SetTransparent(true);
        Actor::AddChild(m_MeshRenderer);
    }

    Planet::~Planet() { LOG_TRACE("Deconstructed::Planet::{0}", GetName()); }

    void Planet::OnUpdate(float deltaTime)
    {
        // vec3 rot { 0.0f, 0.5f, 0.5 };
        // m_MeshRenderer->SetRotation(m_MeshRenderer->GetRotation() + rot * deltaTime * m_RotationSpeed);
    }
}
