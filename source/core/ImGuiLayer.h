#ifndef IMGUI_LAYER_CLASS_H
#define IMGUI_LAYER_CLASS_H

#include "Layer.h"

namespace OpenGLRenderer
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = false;
	};
}

#endif
