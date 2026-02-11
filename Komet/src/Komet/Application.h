#pragma once

#include "Core.h"

#include "Window.h"
#include "Komet/LayerStack.h"
#include "Komet/Events/Event.h"
#include "Komet/Events/ApplicationEvent.h"

#include "Komet/ImGui/ImGuiLayer.h"

namespace Komet {

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}