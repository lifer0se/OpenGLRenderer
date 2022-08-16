#include "Layer.h"

namespace OpenGLRenderer
{
	Layer::Layer() {}
	Layer::~Layer() {}
	void Layer::OnAttach() {}
	void Layer::OnDetach() {}
	void Layer::OnUpdate(float deltaTime) {}
	void Layer::OnEvent(Event& event) {}
	void Layer::ImGuiRender() {}
}
