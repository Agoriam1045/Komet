#pragma once


#include "Komet/Layer.h"

#include "Komet/Events/KeyEvent.h"
#include "Komet/Events/MouseEvent.h"
#include "Komet/Events/ApplicationEvent.h"

namespace Komet {

	class KOMET_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};
}