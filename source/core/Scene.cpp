#include "Scene.h"
#include "Actor.h"
#include "Application.h"
#include "Camera.h"
#include "Logger.h"
#include "MeshRenderer.h"

namespace OpenGLRenderer
{
	Scene::Scene()
	{
		m_Camera = std::make_shared<Camera>(60.0f, 0.01f, 100.0f);
        LOG_TRACE("Constructed::Scene");
	}

    Actor& Scene::GetActor(const char* name)
    {
        if (!m_Actors.count(name))
            LOG_CRITICAL("GetActor: \"{0}\" not found", name);

        return *m_Actors[name];
    }

	void Scene::AddActor(std::shared_ptr<Actor> actor)
	{
		if (m_Actors.count(actor->GetName()))
			return;

        ActorDispatcher dispatcher(actor);
        dispatcher.Dispatch<MeshRenderer>(BIND_FN(AddMeshRenderer));
        dispatcher.Dispatch<Light>(BIND_FN(AddLight));

        m_Actors[actor->GetName()] = actor;
	}

    void Scene::AddMeshRenderer(std::shared_ptr<MeshRenderer> meshRenderer)
    {
        m_MeshRenderers[meshRenderer->GetName()] = meshRenderer;
        auto shader = meshRenderer->GetShader();
        if (!std::count(m_UniqueShaders.begin(), m_UniqueShaders.end(), meshRenderer->GetShader()))
            m_UniqueShaders.push_back(shader);

        for (auto light : m_Lights)
            light->AddShader(shader);
    }

    void Scene::AddLight(std::shared_ptr<Light> light)
    {
        if (m_Lights.size() >= 4)
        {
            LOG_ERROR("Scene::AddActor: Maximum number of lights reached.");
            return;
        }

        m_Lights.push_back(light);
        for (auto& s : m_UniqueShaders)
            light->AddShader(s);
    }

    void Scene::OnUpdate(float deltaTime)
    {
        m_Camera->OnUpdate(deltaTime);
        for (auto& a : m_Actors)
            a.second->OnUpdate(deltaTime);

        Render();
    }

	void Scene::Render()
	{
        for (auto& m : m_MeshRenderers)
            m.second->Draw(*m_Camera);
	}
}
