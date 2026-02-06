#include <Komet.h>

class SandBox : public Komet::Application {
public:
	SandBox() {

	}


	~SandBox() {

	}


};

Komet::Application* Komet::CreateApplication() {
	return new SandBox();
}