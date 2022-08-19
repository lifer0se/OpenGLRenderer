#ifndef SCENE_CLASS_H
#define SCENE_CLASS_H

#include "Actor.h"
#include "Camera.h"
#include "Light.h"
#include "MeshRenderer.h"

using namespace std;

namespace OpenGLRenderer
{
	class Scene
	{
	public:
		Scene();
		~Scene() { LOG_TRACE("Deconstructed::Scene"); };

		inline Camera& GetCamera() { return *m_Camera; };

		Actor& GetActor(const char* name);
        void AddActor(std::shared_ptr<Actor> actor);
		void DeleteActor(const char* name);

        void OnUpdate(float deltaTime);
		void Render();

	private:
        std::shared_ptr<Camera> m_Camera;
		map<const char*, std::shared_ptr<Actor>> m_Actors;
		map<const char*, std::shared_ptr<MeshRenderer>> m_MeshRenderers;
        vector<std::shared_ptr<Light>> m_Lights;
        vector<std::shared_ptr<Shader>> m_UniqueShaders;


        void AddMeshRenderer(std::shared_ptr<MeshRenderer> meshRenderer);
        void AddLight(std::shared_ptr<Light> light);
	};
}

#endif
