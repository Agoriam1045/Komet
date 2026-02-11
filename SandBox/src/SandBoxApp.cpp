#include <Komet.h>

#include "imgui/imgui.h"

class ExampleLayer : public Komet::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Komet::Input::IsKeyPressed(KM_KEY_TAB))
			KM_TRACE("Tab key is pressed! (poll)");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("To Access Mouse Cursor press ESC");
		ImGui::Text("Move with Mouse + W,A,S,D + Q,E");
		ImGui::End();
	}

	void OnEvent(Komet::Event& event) override
	{
		if (event.GetEventType() == Komet::EventType::KeyPressed)
		{
			if (Komet::Input::IsKeyPressed(KM_KEY_TAB))
				KM_TRACE("Tab key is pressed! (event)");
		}
	}
};

class SandBox : public Komet::Application {
public:
	SandBox() 
	{
		PushLayer(new ExampleLayer());
	}


	~SandBox() 
	{
	}


};

Komet::Application* Komet::CreateApplication() {
	return new SandBox();
}