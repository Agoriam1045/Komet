#pragma once
#include "Core.h"
#include "Window.h"
#include "Komet/LayerStack.h"
#include "Komet/Events/Event.h"
#include "Komet/Events/ApplicationEvent.h"
#include "Komet/ImGui/ImGuiLayer.h"
#include "Komet/Renderer/Shader.h"
#include "Komet/Renderer/Camera.h"
#include "Komet/Renderer/Mesh.h"
#include "Komet/Renderer/Texture.h"
// #include "Komet/Renderer/Model.h" // Don't include this here to avoid circular dependency loops

namespace Komet {

    // --- FORWARD DECLARATION (Add this!) ---
    class Model;

    class KOMET_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

    private:
        std::unique_ptr<Window> m_Window;

        std::shared_ptr<Mesh> m_CubeMesh;   // The Companion Cube
        std::unique_ptr<Model> m_Model;     // The Imported Model

        std::unique_ptr<Texture2D> m_Texture;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // Temporary OpenGL handles for basic mesh
        unsigned int m_VertexArray = 0;
        unsigned int m_VertexBuffer = 0;
        unsigned int m_IndexBuffer = 0;

        std::unique_ptr<Shader> m_Shader;
        Camera m_Camera;

        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT (Sandbox)
    Application* CreateApplication();
}