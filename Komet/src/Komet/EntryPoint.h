#pragma once

#ifdef KM_PLATFORM_WINDOWS

extern Komet::Application* Komet::CreateApplication();

int main(int argc, char** argv) {

	auto app = Komet::CreateApplication();
	app->Run();
	delete app;
}

#endif