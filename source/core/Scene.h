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

		Camera* GetCamera();
		void SetCamera(Camera camera);

		void SetLight(Light light);

		Actor& GetActor(const char* name);
        void AddActor(std::shared_ptr<Actor> actor);
		void DeleteActor(const char* name);

		void Render();

	private:
		Camera m_Camera;
        Light m_Light;
		map<const char*, std::shared_ptr<Actor>> m_Actors;
		map<const char*, std::shared_ptr<MeshRenderer>> m_MeshRenderers;
	};
}

#endif
