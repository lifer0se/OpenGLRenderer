#ifndef LAYER_CLASS_H
#define LAYER_CLASS_H

#include "Events/Event.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace OpenGLRenderer
{
	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& event);
		virtual void ImGuiRender();
	};
}

#endif
