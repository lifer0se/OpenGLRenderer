#include "RenderLayer.h"
#include "Light.h"
#include "Icosphere.h"
#include "Primatives/Plane.h"
#include "Primatives/Cube.h"

namespace OpenGLRenderer
{
    RenderLayer::RenderLayer() {};
    RenderLayer::~RenderLayer() {};

    void RenderLayer::OnAttach()
    {
        /* Texture textures[] */
        /* { */
            /* Texture { "./resources/textures/planks.png", "diffuse", 0 }, */
            /* Texture { "./resources/textures/planksSpec.png", "specular", 1 } */
        /* }; */

        /* materialShader->Activate(); */
        /* materialShader->SetInt("diffuse0", textures[0].GetID()); */
        /* materialShader->SetInt("specular0", textures[1].GetID()); */

        /* textures[0].Bind(); */
        /* textures[1].Bind(); */

        m_Scene = std::make_unique<Scene>();
        m_Scene->GetCamera().SetPosition({0.0f, 1.0f, -4.0f});

        std::shared_ptr<Shader> materialShader = std::make_shared<Shader>("./source/shaders/default.vert", "./source/shaders/vertexColorLit.frag");

        Icosphere ico { 4, true };
        std::shared_ptr<MeshRenderer> ico1 = std::make_shared<MeshRenderer>(materialShader, ico.GetMesh(), "Ico1");
        m_Scene->AddActor(ico1);

        std::shared_ptr<Light> light = std::make_shared<Light>();
        m_Scene->AddActor(light);

        LOG_TRACE("RenderLayer::Attached");
    }

    void RenderLayer::OnDetach()
    {
        LOG_TRACE("RenderLayer::Detached");
    }

    void RenderLayer::OnUpdate(float deltaTime)
    {
        m_Scene->GetCamera().OnUpdate(deltaTime);
        m_Scene->Render();
    }

    void RenderLayer::OnEvent(Event& event)
    {
        m_Scene->GetCamera().OnEvent(event);
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
