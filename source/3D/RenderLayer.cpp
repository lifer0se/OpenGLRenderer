#include "RenderLayer.h"
#include "Light.h"
#include "Icosphere.h"
#include "Planet.h"
#include "Primatives/Plane.h"
#include "Primatives/Cube.h"

namespace OpenGLRenderer
{
    RenderLayer::RenderLayer() {};
    RenderLayer::~RenderLayer() {};

    void RenderLayer::OnAttach()
    {
        std::shared_ptr<Shader> planetShader = std::make_shared<Shader>("./source/shaders/default.vert", "./source/shaders/vertexColorLit.frag");
        std::shared_ptr<Shader> seaShader = std::make_shared<Shader>("./source/shaders/sea.vert", "./source/shaders/sea.frag");
        std::shared_ptr<Planet> planet = std::make_shared<Planet>(planetShader, seaShader);
        Application::GetInstance().GetScene().AddActor(planet);

        std::shared_ptr<Light> light = std::make_shared<Light>();
        light->SetPosition({ -2.0f, 2.0f, 0.0f });
        Application::GetInstance().GetScene().AddActor(light);

        LOG_TRACE("RenderLayer::Attached");
    }

    void RenderLayer::OnDetach()
    {
        LOG_TRACE("RenderLayer::Detached");
    }

    void RenderLayer::OnUpdate(float deltaTime)
    {
    }

    void RenderLayer::OnEvent(Event& event)
    {
        Application::GetInstance().GetScene().GetCamera().OnEvent(event);
    }

    void RenderLayer::ImGuiRender()
    {
        static int fps;
        static int frames = 0;
        static double lastTime = glfwGetTime();
        static double startTime = lastTime;
        static ImGuiWindowFlags mainWindowFlags { ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground };
        const ImGuiViewport* viewport { ImGui::GetMainViewport() };
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        ImGui::Begin("Main Window", nullptr, mainWindowFlags);

        ImGui::Text("%d fps\n", fps);

        ImGui::End();

        lastTime = glfwGetTime();
        frames++;
        if (lastTime - startTime > 1.0)
        {
            fps = (int) (frames / (lastTime - startTime));
            startTime = lastTime;
            frames = 0;
        }
    }
}
