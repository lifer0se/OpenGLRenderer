#include "RenderLayer.h"
#include "Light.h"
#include "Primatives/Plane.h"
#include "Primatives/Cube.h"

namespace OpenGLRenderer
{
    RenderLayer::RenderLayer() {};
    RenderLayer::~RenderLayer() {};

	void RenderLayer::OnAttach()
	{
		Texture textures[]
		{
			Texture { "./resources/textures/planks.png", "diffuse", 0 },
			Texture { "./resources/textures/planksSpec.png", "specular", 1 }
		};
		vector<Texture> tex { textures, textures + sizeof(textures) / sizeof(Texture) };


        m_Scene = std::make_unique<Scene>();
		m_Scene->GetCamera()->SetPosition({0.0f, 1.0f, -4.0f});

        std::shared_ptr<Shader> materialShader = std::make_shared<Shader>("./source/shaders/multilight.vert", "./source/shaders/default.frag");
        std::shared_ptr<Shader> lightColorShader = std::make_shared<Shader>("./source/shaders/light.vert", "./source/shaders/light.frag");

        /* std::shared_ptr<MeshRenderer> lightDebugRenderer = std::make_shared<MeshRenderer>( lightShader, lightMesh , "Light1"); */
        /* lightDebugRenderer->SetPosition({0.0f, 0.5f, 0.0f}); */
        /* m_Scene->AddActor(lightDebugRenderer); */

        /* Mesh planeMesh = Plane::Make(); */
        /* planeMesh.Textures = tex; */

        Mesh cubeMesh = Cube::Make();
        cubeMesh.Textures = tex;

        std::shared_ptr<MeshRenderer> floorRenderer1 = std::make_shared<MeshRenderer>(materialShader, cubeMesh, "Floor1");
        floorRenderer1->SetPosition({-1.25f, 0.0f, 0.0f});
        m_Scene->AddActor(floorRenderer1);

        std::shared_ptr<MeshRenderer> floorRenderer2 = std::make_shared<MeshRenderer>(materialShader, cubeMesh, "Floor2");
        floorRenderer2->SetPosition({1.25f, 0.0f, 0.0f});
        m_Scene->AddActor(floorRenderer2);

		Light light {};
		light.SetPosition({ 0.0f, 0.5f, 0.0f });
        light.AddShader(materialShader);

		LOG_TRACE("RenderLayer::Attached");
	}

	void RenderLayer::OnDetach()
	{
		LOG_TRACE("RenderLayer::Detached");
	}

	void RenderLayer::OnUpdate()
	{
        m_Scene->GetCamera()->OnUpdate();
        m_Scene->Render();
	}

	void RenderLayer::OnEvent(Event& event)
	{
        m_Scene->GetCamera()->OnEvent(event);
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
