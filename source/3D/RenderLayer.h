#ifndef RENDER_LAYER_CLASS_H
#define RENDER_LAYER_CLASS_H

#include "Layer.h"
#include "Scene.h"
#include "Application.h"

namespace OpenGLRenderer
{
	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void ImGuiRender() override;


    private:
        std::unique_ptr<Scene> m_Scene;
	};
}

#endif
