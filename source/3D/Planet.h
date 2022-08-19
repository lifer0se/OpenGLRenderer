#ifndef PLANET_CLASS_H
#define PLANET_CLASS_H

#include "MeshRenderer.h"

namespace OpenGLRenderer
{
    class Planet : public Actor
    {
    public:
        Planet(std::shared_ptr<Shader> planetShader, std::shared_ptr<Shader> seaShader);
        ~Planet();

        virtual void OnUpdate(float deltaTime) override;

    private:
        std::shared_ptr<MeshRenderer> m_MeshRenderer;

        float m_RotationSpeed = 0.1f;
    };
}
#endif
