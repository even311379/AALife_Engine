#include <AALife_Engine.h>

class Sandbox : public ale::Application
{
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};


ale::Application* ale::CreateApplication()
{
	return new Sandbox();
}