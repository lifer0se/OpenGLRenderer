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
		m_Camera = Camera(60.0f, 0.01f, 100.0f);
        LOG_TRACE("Constructed::Scene");
	}

	Camera* Scene::GetCamera()
	{
		return &m_Camera;
	}

	void Scene::SetCamera(Camera camera)
	{
		m_Camera = camera;
	}

    Actor& Scene::GetActor(const char* name)
    {
        if (!m_Actors.count(name))
        {
            LOG_ERROR("GetActor: \"{0}\" not found", name);
        }
        return *m_Actors[name];
    }

	void Scene::AddActor(std::shared_ptr<Actor> actor)
	{
		if (m_Actors.count(actor->GetName()))
			return;

        m_Actors[actor->GetName()] = actor;

		std::shared_ptr<MeshRenderer> meshRenderer = std::dynamic_pointer_cast<MeshRenderer>(actor);
		if (meshRenderer)
        {
            m_MeshRenderers[actor->GetName()] = meshRenderer;
            cout << actor->GetName() << endl;
        }
	}

	void Scene::Render()
	{
        for (auto& m : m_MeshRenderers)
        {
            m.second->Draw(&m_Camera);
        }
	}
}
