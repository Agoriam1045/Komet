#pragma once

#include "Core.h"

namespace Komet {

	class KOMET_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};


	Application* CreateApplication();

}