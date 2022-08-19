#include "Application.h"
#include "Input.h"
#include "RenderLayer.h"


namespace OpenGLRenderer
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

        m_Scene = std::make_unique<Scene>();
        m_Scene->GetCamera().SetPosition({0.0f, 1.0f, -4.0f});

        PushLayer(new RenderLayer());
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::Update()
    {
        while (m_Running)
        {
            glClearColor(0.12f, 0.15f, 0.20f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            float time = (float)glfwGetTime();
            float deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            m_Scene->OnUpdate(deltaTime);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->ImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Application::OnWindowResized));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent event)
    {
        m_Running = false;

        LOG_INFO("Application::{0}", event);
        return true;
    }

    bool Application::OnWindowResized(WindowResizeEvent event)
    {
        int width = Application::GetInstanceWindow().GetWidth();
        int height = Application::GetInstanceWindow().GetHeight();
        glViewport(0, 0, width, height);
        return false;
    }

}
