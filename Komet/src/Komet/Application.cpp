#include "kmpch.h"
#include "Application.h"
#include "Komet/Log.h"
#include "Input.h"
#include "Keycodes.h"
#include "Komet/Prefabs/Primitive.h"
#include "Komet/Renderer/Model.h"


#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

namespace Komet {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Camera(glm::vec3(0.0f, 0.0f, 3.0f))
    {
        KM_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


        // Enable Depth Testing
        glEnable(GL_DEPTH_TEST);

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // Load Shaders
        m_Shader = std::make_unique<Shader>("Komet/src/Komet/Shaders/default.VS.glsl",
            "Komet/src/Komet/Shaders/default.FS.glsl");
        m_CubeMesh = Primitive::Cube();

        m_Texture = std::make_unique<Texture2D>("Komet/src/Assets/Textures/CompanionCube.png");

        m_Model = std::make_unique<Model>("Komet/src/Assets/Models/HollowKnight/Hornet.fbx");

        auto window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event) {
            static float lastX = event.GetX();
            static float lastY = event.GetY();

            float xOffset = event.GetX() - lastX;
            float yOffset = lastY - event.GetY();

            lastX = event.GetX();
            lastY = event.GetY();

            m_Camera.ProcessMouseMovement(xOffset, yOffset);
            return false;
            });


        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }

        if (Input::IsKeyPressed(KM_KEY_ESCAPE)) {
            auto window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            //Delta Time
            float time = (float)glfwGetTime();
            float deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            // Input Handling
            if (Input::IsKeyPressed(KM_KEY_W)) m_Camera.ProcessKeyboard(FORWARD, deltaTime);
            if (Input::IsKeyPressed(KM_KEY_S)) m_Camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (Input::IsKeyPressed(KM_KEY_A)) m_Camera.ProcessKeyboard(LEFT, deltaTime);
            if (Input::IsKeyPressed(KM_KEY_D)) m_Camera.ProcessKeyboard(RIGHT, deltaTime);
            if (Input::IsKeyPressed(KM_KEY_Q)) m_Camera.ProcessKeyboard(DOWN, deltaTime);
            if (Input::IsKeyPressed(KM_KEY_E)) m_Camera.ProcessKeyboard(UP, deltaTime);

            //Render Prep
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Global Setup (Camera & Lights)
            float aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();
            glm::mat4 view = m_Camera.GetViewMatrix();
            glm::mat4 projection = m_Camera.GetProjectionMatrix(aspectRatio);

            m_Shader->Bind();
            m_Texture->Bind(0);
            m_Shader->SetInt("u_Material.diffuse", 0);

            //View & Projection (Same for both objects)
            m_Shader->SetMat4("u_View", view);
            m_Shader->SetMat4("u_Projection", projection);

            //Light & Camera Pos (Same for both objects)
            m_Shader->SetFloat3("u_ViewPos", m_Camera.GetPosition());
            m_Shader->SetFloat3("u_Light.position", glm::vec3(1.2f, 1.0f, 2.0f));
            m_Shader->SetFloat3("u_Light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
            m_Shader->SetFloat3("u_Light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            m_Shader->SetFloat3("u_Light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

            //Material Defaults
            m_Shader->SetFloat3("u_Material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
            m_Shader->SetFloat("u_Material.shininess", 32.0f);


            // ============================================================
            // COMPANION CUBE MODEL
            // ============================================================
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, -0.5f, -5.0f));

                m_Shader->SetMat4("u_Model", model);
                m_CubeMesh->Draw();
            }

            // ============================================================
			// HORNET MODEL (IMPORTED)
            // ============================================================
            if (m_Model)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, 0.5f, -5.0f));
				model = glm::scale(model, glm::vec3(0.005f)); //Model was way too big, had to scale it down

                m_Shader->SetMat4("u_Model", model);
                m_Model->Draw(*m_Shader);
            }

            // Layer Updates & ImGui
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}