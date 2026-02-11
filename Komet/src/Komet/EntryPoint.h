#pragma once

#ifdef KM_PLATFORM_WINDOWS

extern Komet::Application* Komet::CreateApplication();

int main(int argc, char** argv) {

	Komet::Log::Init();
	KM_CORE_WARN("Initialized Log!");
	int a = 5;
	KM_CORE_INFO("Hello! Var={0}", a);

	auto app = Komet::CreateApplication();
	app->Run();
	delete app;
}

#endif