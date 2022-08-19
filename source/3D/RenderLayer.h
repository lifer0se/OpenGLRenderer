#ifndef RENDER_LAYER_CLASS_H
#define RENDER_LAYER_CLASS_H

#include "Application.h"
#include "Layer.h"

namespace OpenGLRenderer
{
	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnEvent(Event& event) override;
		virtual void ImGuiRender() override;
	};
}

#endif
